// Learning project from Udemy course


#include "STUCharacterMovementComponent.h"

#include "ShootThemUp/Player/STUCharacterBase.h"


float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const auto MaxSpeed = Super::GetMaxSpeed();

    auto* Character = GetOwner<ASTUCharacterBase>();
    return IsValid(Character) && Character->GetIsRunning() ? MaxSpeed * RunModifier: MaxSpeed;
}
