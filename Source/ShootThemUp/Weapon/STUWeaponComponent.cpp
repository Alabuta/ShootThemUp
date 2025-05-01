// Learning project from Udemy course


#include "STUWeaponComponent.h"

#include "STUWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"


USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::StartFire()
{
    if (!IsValid(CurrentWeapon))
    {
        return;
    }

    CurrentWeapon->StartFire();
}

void USTUWeaponComponent::StopFire()
{
    if (!IsValid(CurrentWeapon))
    {
        return;
    }

    CurrentWeapon->StopFire();
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    SpawnWeapon();
}

void USTUWeaponComponent::SpawnWeapon()
{
    auto* World = GetWorld();
    if (!IsValid(World))
    {
        return;
    }

    auto* OwnerCharacter = GetOwner<ACharacter>();
    if (!IsValid(OwnerCharacter))
    {
        return;
    }

    CurrentWeapon = World->SpawnActor<ASTUWeaponBase>(WeaponClass);
    if (!IsValid(CurrentWeapon))
    {
        return;
    }

    const FAttachmentTransformRules AttachmentRules{EAttachmentRule::SnapToTarget, false};
    CurrentWeapon->AttachToComponent(OwnerCharacter->GetMesh(), AttachmentRules, AttachSocketName);
    CurrentWeapon->SetOwner(OwnerCharacter);
}
