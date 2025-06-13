// Learning project from Udemy course


#include "Tasks/STUNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


USTUNextLocationTask::USTUNextLocationTask()
{
    NodeName = TEXT("Next Location");
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto* Controller = OwnerComp.GetAIOwner();
    auto* Blackboard = OwnerComp.GetBlackboardComponent();

    if (!IsValid(Controller) || !IsValid(Blackboard))
    {
        return EBTNodeResult::Failed;
    }

    const auto Pawn = Controller->GetPawn();
    if (!IsValid(Pawn))
    {
        return EBTNodeResult::Failed;
    }

    const auto* NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
    if (!IsValid(NavSystem))
    {
        return EBTNodeResult::Failed;
    }

    FNavLocation NavLocation;
    if (!NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Radius, NavLocation))
    {
        return EBTNodeResult::Failed;
    }

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

    return EBTNodeResult::Succeeded;
}
