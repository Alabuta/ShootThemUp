// Learning project from Udemy course


#include "STUPlayerWidget.h"

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
