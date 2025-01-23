

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

	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APlayerPawn::OnBeginOverlap);

	OnTakeAnyDamage.AddDynamic(this, &APlayerPawn::HandleTakeAnyDamage);
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
		// Move
		EnhancedInputComponent->BindAction(ActionMove, ETriggerEvent::Triggered, this, &APlayerPawn::Move);
		EnhancedInputComponent->BindAction(ActionLook, ETriggerEvent::Triggered, this, &APlayerPawn::Look);
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
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(ForwardDirection, MovementVector.Y);
		// Alina: Player turns left/right with Yaw input, no safe normal for Movement vector is needed
		AddControllerYawInput(MovementVector.X);
		//AddMovementInput(RightDirection, MovementVector.X); // Alternative commented out -- no animations for this one
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

void APlayerPawn::HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MaxHealth);

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Red, FString::Printf(TEXT("Health: %f"), CurrentHealth));
	}
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
