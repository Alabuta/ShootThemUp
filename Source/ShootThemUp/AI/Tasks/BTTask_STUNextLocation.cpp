// Learning project from Udemy course


#include "Tasks/BTTask_STUNextLocation.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_STUNextLocation::UBTTask_STUNextLocation()
{
    NodeName = TEXT("Next Location");
}

EBTNodeResult::Type UBTTask_STUNextLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

    auto Location = Pawn->GetActorLocation();
    if (!bSelfCenter)
    {
        if (const auto* CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
            IsValid(CenterActor))
        {
            Location = CenterActor->GetActorLocation();
        }
    }

    FNavLocation NavLocation;
    if (!NavSystem->GetRandomReachablePointInRadius(Location, Radius, NavLocation))
    {
        return EBTNodeResult::Failed;
    }

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

    return EBTNodeResult::Succeeded;
}
