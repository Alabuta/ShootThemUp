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

    if (const auto* HealthComponent = FSTUUtils::GetPawnComponent<USTUHealthComponent>(Pawn);
        !IsValid(HealthComponent) || HealthComponent->IsDead())
    {
        return false;
    }

    const auto* WeaponComponent = FSTUUtils::GetPawnComponent<USTUWeaponComponent>(Pawn);
    if (!IsValid(WeaponComponent))
    {
        return false;
    }

    return WeaponComponent->TryAddAmmo(WeaponType, ClipsAmount);

}
