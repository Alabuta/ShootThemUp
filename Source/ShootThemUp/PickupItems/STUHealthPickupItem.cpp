// Learning project from Udemy course


#include "STUHealthPickupItem.h"

#include "GameFramework/Pawn.h"
#include "ShootThemUp/Components/STUHealthComponent.h"


bool ASTUHealthPickupItem::GivePickupItemTo(APawn* Pawn)
{
    if (!IsValid(Pawn))
    {
        return false;
    }

    auto* HealthComponent = Pawn->GetComponentByClass<USTUHealthComponent>();
    if (!IsValid(HealthComponent) || HealthComponent->IsDead())
    {
        return false;
    }

    return HealthComponent->TryAddHealth(HealthAmount);
}
