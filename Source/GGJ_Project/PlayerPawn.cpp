

#include "PlayerPawn.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AI/BaseEnemyCharacter.h"
#include "Interactible.h"
#include "Abilities/PlayerAbilityComponent.h"
#include "Abilities/RangedShot.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerPawn::APlayerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	
	GetCapsuleComponent()->InitCapsuleSize(50.f, 50.f);

	// Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bUsePawnControlRotation = true;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	// Movement
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Abilities
	Abilities = CreateDefaultSubobject<UPlayerAbilityComponent>(TEXT("Abilities"));

	GunMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	GunMeshComp->SetupAttachment(GetMesh());

	// Add sound
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComp->SetupAttachment(RootComponent);
}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	// Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	// Overlaps
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerPawn::OnBeginOverlap);
	// Take Damage
	OnTakeAnyDamage.AddDynamic(this, &APlayerPawn::HandleTakeAnyDamage);
	// Attach GunMeshComp to spine bone
	AttachGun(false);
}

void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &APlayerPawn::Look);
		EnhancedInputComponent->BindAction(ActionShoot, ETriggerEvent::Triggered, this, &APlayerPawn::Shoot);
	}
}


void APlayerPawn::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDirection, MovementVector.Y * SpeedMultiplier);
		// Alina: Player turns left/right with Yaw input, no safe normal for Movement vector is needed
		AddControllerYawInput(MovementVector.X);
		// Alternative commented out -- no animations for this one
		//const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		//AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APlayerPawn::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerPawn::Shoot(const FInputActionValue& Value)
{
	Abilities->RangedShot->UseAbility();
}

void APlayerPawn::OnTriggerPulled()
{
	Abilities->RangedShot->OnTriggerPulled();
}

void APlayerPawn::BoostSpeed(float BoostTimer)
{
	SpeedMultiplier = 2;
	GetCharacterMovement()->MaxWalkSpeed = 1200;
	GetWorldTimerManager().SetTimer(BoostSpeedTimer, this, &APlayerPawn::ResetSpeed, BoostTimer, false);
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Speed Boosted: %g"), GetCharacterMovement()->MaxWalkSpeed));
	}
}

void APlayerPawn::ResetSpeed()
{
	SpeedMultiplier = 1;
	GetCharacterMovement()->MaxWalkSpeed = 600;
}

void APlayerPawn::AttachGun(const bool bShouldBeInHand)
{
	if (bShouldBeInHand)
	{
		FName SocketHands = "GunPlay"; 
		GunMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketHands);
	}
	else
	{
		FName SocketSpine = "GunIdle"; 
		GunMeshComp->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, SocketSpine);
	}
}

void APlayerPawn::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MaxHealth);
	if (CurrentHealth == 0)
	{
		DieDramatically();
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, FString::Printf(TEXT("Health: %f"), CurrentHealth));
	}
}

void APlayerPawn::DieDramatically()
{
	// Play sad music
	if(SadMusic)
		UGameplayStatics::PlaySound2D(this, SadMusic);

	// Detach camera
	Camera->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	
	// Disable any input and MovementComponent for capsule movement
	DisableInput(Cast<APlayerController>(Controller));
	GetCharacterMovement()->DisableMovement();

	// Let the gun fly
	GunMeshComp->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

	// Enable ragdoll for pawn mesh
	FName Collision = FName(TEXT("BlockAllDynamic"));
	GetMesh()->SetCollisionProfileName(Collision, true);
	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	// Enable ragdoll for gun mesh
	GunMeshComp->SetCollisionProfileName(Collision, true);
	GunMeshComp->SetSimulatePhysics(true);
	GunMeshComp->WakeAllRigidBodies();

	// Move capsule in the sky, so that bots stop attacking it
	UCapsuleComponent* CapsuleForCamera = GetCapsuleComponent();
	FVector Location = CapsuleForCamera->GetComponentLocation();
	CapsuleForCamera->SetWorldLocation(FVector(Location.X, Location.Y, Location.Z+1000.f));
	
	// Set timer to go to menu
	GetWorldTimerManager().SetTimer(TimerOpenMenu, this, &APlayerPawn::LoadMenu, 5.f, false);
}

void APlayerPawn::LoadMenu()
{
	FName LevelName = "MenuMap";
	FLatentActionInfo LatentInfo;
	UGameplayStatics::OpenLevel(this, LevelName, true);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("Health: %f, called load menu"), CurrentHealth));
	}
}

float APlayerPawn::GetHealth()
{
	return CurrentHealth / MaxHealth;
}

void APlayerPawn::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherActor->GetClass()->ImplementsInterface(UInteractible::StaticClass()))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, FString::Printf(TEXT("Interacted with %s"), *OtherActor->GetName()));
		}
		IInteractible::Execute_Interact(OtherActor, this);
	}
}
