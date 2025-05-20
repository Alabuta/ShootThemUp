// Learning project from Udemy course


#include "STUPlayerWidget.h"

#include "Components/STUWeaponComponent.h"
#include "GameFramework/Pawn.h"
#include "ShootThemUp/Components/STUHealthComponent.h"


float USTUPlayerWidget::GetHealthPercent() const
{
    const auto* OwningPlayerPawn = GetOwningPlayerPawn();
    if (!IsValid(OwningPlayerPawn))
    {
        return 0.f;
    }

    const auto* HealthComponent = OwningPlayerPawn->GetComponentByClass<USTUHealthComponent>();
    if (!IsValid(HealthComponent))
    {
        return 0.f;
    }

    return HealthComponent->GetHealthPercent();
}

bool USTUPlayerWidget::GetCurrentWeaponUIData(FSTUWeaponUIData& UIData) const
{
    const auto* WeaponComponent = GetWeaponComponent();
    if (!IsValid(WeaponComponent))
    {
        return false;
    }

    return WeaponComponent->GetUIData(UIData);
}

bool USTUPlayerWidget::GetCurrentWeaponAmmoData(FSTUAmmoData& AmmoData) const
{
    const auto* WeaponComponent = GetWeaponComponent();
    if (!IsValid(WeaponComponent))
    {
        return false;
    }

    return WeaponComponent->GetAmmoData(AmmoData);
}

const USTUWeaponComponent* USTUPlayerWidget::GetWeaponComponent() const
{
    const auto* OwningPlayerPawn = GetOwningPlayerPawn();
    if (!IsValid(OwningPlayerPawn))
    {
        return nullptr;
    }

    return OwningPlayerPawn->GetComponentByClass<USTUWeaponComponent>();
}
