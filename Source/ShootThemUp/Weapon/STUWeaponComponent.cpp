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

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto* Weapon : Weapons)
    {
        if (IsValid(Weapon))
        {
            Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
            Weapon->Destroy();
        }
    }

    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
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

void USTUWeaponComponent::NextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    SpawnWeapons();
    EquipWeapon(0);
}

void USTUWeaponComponent::SpawnWeapons()
{
    Weapons.Empty();

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

    for (auto WeaponClass : WeaponClasses)
    {
        auto* Weapon = World->SpawnActor<ASTUWeaponBase>(WeaponClass);
        if (!IsValid(Weapon))
        {
            continue;
        }

        Weapon->SetOwner(OwnerCharacter);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, OwnerCharacter->GetMesh(), WeaponArmorySocketName);
    } 
}

void USTUWeaponComponent::EquipWeapon(const int32 WeaponIndex)
{
    if (!Weapons.IsValidIndex(WeaponIndex))
    {
        return;
    }

    const auto* OwnerCharacter = GetOwner<ACharacter>();
    if (!IsValid(OwnerCharacter))
    {
        return;
    }

    if (IsValid(CurrentWeapon))
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponEquipSocketName);
}

void USTUWeaponComponent::AttachWeaponToSocket(
    ASTUWeaponBase* Weapon,
    USceneComponent* AttachComponent,
    const FName SocketName)
{
    if (!IsValid(Weapon) || !IsValid(AttachComponent))
    {
        return;
    }

    const FAttachmentTransformRules AttachmentRules{EAttachmentRule::SnapToTarget, false};
    Weapon->AttachToComponent(AttachComponent, AttachmentRules, SocketName);
}
