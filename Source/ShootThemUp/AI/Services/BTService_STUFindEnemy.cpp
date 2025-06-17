// Learning project from Udemy course


#include "Services/BTService_STUFindEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUAIPerceptionComponent.h"


UBTService_STUFindEnemy::UBTService_STUFindEnemy()
{
    NodeName = TEXT("Find Enemy");
}

void UBTService_STUFindEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    TIckNodeInternal(OwnerComp);

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTService_STUFindEnemy::TIckNodeInternal(UBehaviorTreeComponent& OwnerComp) const
{
    auto* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!IsValid(BlackboardComponent))
    {
        return;
    }

    const auto* Controller = OwnerComp.GetAIOwner();
    if (!IsValid(Controller))
    {
        return;
    }

    const auto* AIPerceptionComponent = Controller->GetComponentByClass<USTUAIPerceptionComponent>();
    if (!IsValid(AIPerceptionComponent))
    {
        return;
    }

    BlackboardComponent->SetValueAsObject(EnemyActorKey.SelectedKeyName, AIPerceptionComponent->GetClosestEnemy());
}
