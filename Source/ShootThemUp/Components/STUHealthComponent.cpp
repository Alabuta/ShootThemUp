// Learning project from Udemy course


#include "STUHealthComponent.h"

#include "Logging/StructuredLog.h"
#include "ShootThemUp/Player/STUCharacterBase.h"


USTUHealthComponent::USTUHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor,
    float Damage,
    const UDamageType* DamageType,
    AController* Instigator,
    AActor* DamageCauser)
{
    CurrentHealth -= Damage;
}

void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    CurrentHealth = MaxHealth;

    if (auto* OwnerCharacter = GetOwner<ASTUCharacterBase>(); IsValid(OwnerCharacter))
    {
        OwnerCharacter->OnTakeAnyDamage.AddDynamic(this, &ThisClass::OnTakeAnyDamage);
    }
}

