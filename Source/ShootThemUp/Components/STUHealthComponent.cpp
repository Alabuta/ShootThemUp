// Learning project from Udemy course


#include "STUHealthComponent.h"

#include "TimerManager.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "Logging/StructuredLog.h"
#include "ShootThemUp/Player/STUCharacterBase.h"


USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

bool USTUHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(CurrentHealth);
}

bool USTUHealthComponent::TryAddHealth(const float HealthAmount)
{
    if (IsDead() || IsHealthFull())
    {
        return false;
    }

    SetHealth(CurrentHealth + HealthAmount);
    return true;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0.f);

    SetHealth(MaxHealth);

    if (auto* OwnerCharacter = GetOwner<ASTUCharacterBase>(); IsValid(OwnerCharacter))
    {
        OwnerCharacter->OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor,
    float Damage,
    const UDamageType* DamageType,
    AController* Instigator,
    AActor* DamageCauser)
{
    if (Damage <= 0.f || IsDead())
    {
        return;
    }

    const auto* World = GetWorld();
    if (!IsValid(World))
    {
        return;
    }

    SetHealth(CurrentHealth - Damage);

    World->GetTimerManager().ClearTimer(HealthTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (bAutoHeal)
    {
        World->GetTimerManager().SetTimer(
            HealthTimerHandle,
            this,
            &ThisClass::HealUpdate,
            HealUpdateTime,
            true,
            HealStartDelay
        );
    }
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(CurrentHealth + HealAmount);

    if (IsHealthFull())
    {
        if (const auto* World = GetWorld(); IsValid(World))
        {
            GetWorld()->GetTimerManager().ClearTimer(HealthTimerHandle);
        }
    }
}

void USTUHealthComponent::SetHealth(const float NewHealth)
{
    CurrentHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);
}
