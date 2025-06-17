// Learning project from Udemy course


#include "Services/BTService_STUFireService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUWeaponComponent.h"


UBTService_STUFireService::UBTService_STUFireService()
{
    NodeName = TEXT("Fire");
}

void UBTService_STUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    TickNodeInternal(OwnerComp);

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTService_STUFireService::TickNodeInternal(UBehaviorTreeComponent& OwnerComp) const
{
    const auto* BlackboardComponent = OwnerComp.GetBlackboardComponent();
    if (!IsValid(BlackboardComponent))
    {
        return;
    }

    const auto* Controller = OwnerComp.GetAIOwner();
    if (!IsValid(Controller))
    {
        return;
    }

    const auto Pawn = Controller->GetPawn();
    if (!IsValid(Pawn))
    {
        return;
    }

    auto* WeaponComponent = Pawn->GetComponentByClass<USTUWeaponComponent>();
    if (!IsValid(WeaponComponent))
    {
        return;
    }

    if (IsValid(BlackboardComponent->GetValueAsObject(EnemyActorKey.SelectedKeyName)))
    {
        WeaponComponent->StartFire();
    }
    else
    {
        WeaponComponent->StopFire();
    }
}
