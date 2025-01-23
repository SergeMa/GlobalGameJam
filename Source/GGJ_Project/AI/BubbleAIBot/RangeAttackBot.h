
#pragma once

#include "CoreMinimal.h"
#include "GGJ_Project/AI/BaseEnemyCharacter.h"
#include "RangeAttackBot.generated.h"



class AProjectile;

UCLASS()
class GGJ_PROJECT_API ARangeAttackBot : public ABaseEnemyCharacter
{
	GENERATED_BODY()
public:
	ARangeAttackBot();

	UFUNCTION()
	void RangeAttack(AActor *Actor);
	
	virtual void Tick(float DeltaTime) override;

	bool CheckDistance();

	void StartAttack();
	void StopAttack();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	TSubclassOf<AProjectile> ProjectileClass;

	FTimerHandle Timer;
};
