// Learning project from Udemy course


#include "STUWeaponComponent.h"

#include "STUWeaponBase.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "ShootThemUp/Animations/STUAnimNotify_EquipFinished.h"


USTUWeaponComponent::USTUWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentWeaponIndex = 0;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(0);
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
    if (!CanFire())
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
    if (!CanEquip())
    {
        return;
    }

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

bool USTUWeaponComponent::CanFire() const
{
    return IsValid(CurrentWeapon) && !bIsEquipInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !bIsEquipInProgress;
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

    bIsEquipInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    const auto* OwnerCharacter = GetOwner<ACharacter>();
    if (!IsValid(OwnerCharacter))
    {
        return;
    }

    if (!IsValid(MeshComp) || OwnerCharacter->GetMesh() != MeshComp)
    {
        return;
    }

    bIsEquipInProgress = false;
    
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage) const
{
    auto* OwnerCharacter = GetOwner<ACharacter>();
    if (!IsValid(OwnerCharacter))
    {
        return;
    }

    OwnerCharacter->PlayAnimMontage(AnimMontage);
}

void USTUWeaponComponent::InitAnimations()
{
    if (!IsValid(EquipAnimMontage))
    {
        return;
    }

    const auto* AnimNotifyEvent = EquipAnimMontage->Notifies.FindByPredicate(
        [](const FAnimNotifyEvent& NotifyEvent)
        {
            return NotifyEvent.Notify.IsA<USTUAnimNotify_EquipFinished>();
        });

    auto* EquipFinishedNotify = Cast<USTUAnimNotify_EquipFinished>(
        AnimNotifyEvent != nullptr ? AnimNotifyEvent->Notify : nullptr);
    if (!IsValid(EquipFinishedNotify))
    {
        return;
    }

    EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
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
