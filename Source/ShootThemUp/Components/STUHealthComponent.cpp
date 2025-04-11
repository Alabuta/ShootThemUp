// Learning project from Udemy course


#include "STUHealthComponent.h"

#include "GameFramework/DamageType.h"
#include "Logging/StructuredLog.h"
#include "ShootThemUp/Player/STUCharacterBase.h"


USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;
    OnHealthChanged.Broadcast(CurrentHealth);

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

    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}