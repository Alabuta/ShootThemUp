// Learning project from Udemy course


#include "STUAmmoPickupItem.h"

#include "Components/STUWeaponComponent.h"
#include "ShootThemUp/Components/STUHealthComponent.h"
#include "ShootThemUp/Player/FSTUUtils.h"


bool ASTUAmmoPickupItem::GivePickupItemTo(APawn* Pawn)
{
    if (!IsValid(Pawn))
    {
        return false;
    }

    if (const auto* HealthComponent = Pawn->GetComponentByClass<USTUHealthComponent>();
        !IsValid(HealthComponent) || HealthComponent->IsDead())
    {
        return false;
    }

    const auto* WeaponComponent = Pawn->GetComponentByClass<USTUWeaponComponent>();
    if (!IsValid(WeaponComponent))
    {
        return false;
    }

    return WeaponComponent->TryAddAmmo(WeaponType, ClipsAmount);

}
