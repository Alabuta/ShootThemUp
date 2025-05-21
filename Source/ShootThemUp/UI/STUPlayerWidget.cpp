// Learning project from Udemy course


#include "STUPlayerWidget.h"

#include "Components/STUWeaponComponent.h"
#include "GameFramework/Pawn.h"
#include "ShootThemUp/Components/STUHealthComponent.h"


float USTUPlayerWidget::GetHealthPercent() const
{
    const auto* HealthComponent = GetOwningPlayerComponent<USTUHealthComponent>();
    return IsValid(HealthComponent) && HealthComponent->GetHealthPercent();
}

bool USTUPlayerWidget::GetCurrentWeaponUIData(FSTUWeaponUIData& UIData) const
{
    const auto* WeaponComponent = GetOwningPlayerComponent<USTUWeaponComponent>();
    return IsValid(WeaponComponent) && WeaponComponent->GetUIData(UIData);
}

bool USTUPlayerWidget::GetCurrentWeaponAmmoData(FSTUAmmoData& AmmoData) const
{
    const auto* WeaponComponent = GetOwningPlayerComponent<USTUWeaponComponent>();
    return IsValid(WeaponComponent) && WeaponComponent->GetAmmoData(AmmoData);
}

bool USTUPlayerWidget::IsPlayerAlive() const
{
    const auto* HealthComponent = GetOwningPlayerComponent<USTUHealthComponent>();
    return IsValid(HealthComponent) && !HealthComponent->IsDead();
}

bool USTUPlayerWidget::IsPlayerSpectator() const
{
    const auto* PlayerController = GetOwningPlayer();
    return IsValid(PlayerController) && PlayerController->GetStateName() == NAME_Spectating;
}

template <class T>
T* USTUPlayerWidget::GetOwningPlayerComponent() const
{
    const auto* OwningPlayerPawn = GetOwningPlayerPawn();
    if (!IsValid(OwningPlayerPawn))
    {
        return nullptr;
    }

    return OwningPlayerPawn->GetComponentByClass<T>();
}
