
#include "GGJ_Project/AI/BubbleAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "GGJ_Project/PlayerPawn.h"


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


