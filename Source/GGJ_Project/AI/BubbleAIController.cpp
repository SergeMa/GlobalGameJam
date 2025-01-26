
#include "GGJ_Project/AI/BubbleAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "GGJ_Project/PlayerPawn.h"
#include "GGJ_Project/AI/BubbleAIBot/RangeAttackBot.h"
#include "Kismet/GameplayStatics.h"


ABubbleAIController::ABubbleAIController()
{
	Perception = CreateDefaultSubobject<UAIPerceptionComponent>("Perception");
	Perception->OnTargetPerceptionUpdated.AddDynamic(this, &ABubbleAIController::OnTargetPerceptionUpdated);
}
void ABubbleAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunBehaviorTree(BT);
}

void ABubbleAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	UBlackboardComponent* BB = GetBlackboardComponent();
	if (!BB ||!Actor)return;

	if (Actor->IsA<APlayerPawn>()) {
		BB->SetValueAsObject("Character", Actor);
		
	}


}

void ABubbleAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UBlackboardComponent* BlackBoard = GetBlackboardComponent();
	if (!BlackBoard)return;

	FVector CharacterLocation;
	APlayerPawn* MyCharacter = Cast<APlayerPawn>(UGameplayStatics::GetActorOfClass(GetWorld(), APlayerPawn::StaticClass()));
	if (MyCharacter)
	{
	BlackBoard->SetValueAsObject("Character", MyCharacter);
		
	}
	
}

AActor* ABubbleAIController::GetcurentActor()
{
	UBlackboardComponent* BB = GetBlackboardComponent();
	AActor * CurrActor = Cast<AActor>(BB->GetValueAsObject("Character"));
	if (!BB || !CurrActor)return nullptr;

	return CurrActor;


}


