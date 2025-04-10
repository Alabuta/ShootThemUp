// Learning project from Udemy course


#include "STUHealthComponent.h"

#include "Logging/StructuredLog.h"
#include "ShootThemUp/Player/STUCharacterBase.h"


DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);


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

    UE_LOGFMT(LogHealthComponent, Display, "Damage: {0}", Damage);
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

