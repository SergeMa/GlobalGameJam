

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseEnemyCharacter.generated.h"

class UNiagaraSystem;

UCLASS()
class GGJ_PROJECT_API ABaseEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack();
	virtual void OnDeath();

	UFUNCTION()
	void HandleTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
		AController* InstigatedBy, AActor* DamageCauser);


	int GetHealth() { return Health; }
	void SetHealth(int Value) { Health = Value; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	UAudioComponent* AudioComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundWave* SoundDeath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	USoundWave* AttackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Experience)
	int Experience = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = DmgText)
	TSubclassOf<AActor> DmgTextActorClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Niagara)
	UNiagaraSystem* Niagara;

	
private:
	int Health;
	int MaxHealth=100;
};
