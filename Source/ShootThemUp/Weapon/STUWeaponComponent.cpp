// Learning project from Udemy course


#include "STUWeaponComponent.h"

#include "STUWeaponBase.h"
#include "Animation/AnimMontage.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "ShootThemUp/Animations/STUAnimNotify_EquipFinished.h"
#include "ShootThemUp/Animations/STUAnimNotify_ReloadFinished.h"


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
    CurrentReloadAnimMontage = nullptr;

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

void USTUWeaponComponent::Reload()
{
    if (!CanReload())
    {
        return;
    }

    StopFire();

    bIsReloadInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTUWeaponComponent::CanFire() const
{
    return IsValid(CurrentWeapon) && !bIsEquipInProgress && !bIsReloadInProgress;
}

bool USTUWeaponComponent::CanEquip() const
{
    return !bIsEquipInProgress && !bIsReloadInProgress;
}

bool USTUWeaponComponent::CanReload() const
{
    return IsValid(CurrentWeapon) &&!bIsEquipInProgress && !bIsReloadInProgress;
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

    for (const auto& Data : WeaponData)
    {
        auto* Weapon = World->SpawnActor<ASTUWeaponBase>(Data.WeaponClass);
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

    StopFire();

    if (IsValid(CurrentWeapon))
    {
        AttachWeaponToSocket(CurrentWeapon, OwnerCharacter->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];

    const auto* CurrenWeaponData = WeaponData.FindByPredicate(
        [this](const FSTUWeaponData& Data)
        {
            return Data.WeaponClass == CurrentWeapon->GetClass();
        });

    CurrentReloadAnimMontage = CurrenWeaponData != nullptr ? CurrenWeaponData->ReloadAnimMontage : nullptr;

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

void USTUWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
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

    bIsReloadInProgress = false;
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

    if (auto* EquipFinishedNotify = FindFirstAnimNotify<USTUAnimNotify_EquipFinished>(EquipAnimMontage);
        IsValid(EquipFinishedNotify))
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);
    }

    for (const auto& Data : WeaponData)
    {
        auto* ReloadFinishedNotify = FindFirstAnimNotify<USTUAnimNotify_ReloadFinished>(Data.ReloadAnimMontage);
        if (!IsValid(ReloadFinishedNotify))
        {
            continue;
        }

        ReloadFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadFinished);
    }
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

template <class T>
T* USTUWeaponComponent::FindFirstAnimNotify(const UAnimSequenceBase* AnimSequence)
{
    if (!IsValid(AnimSequence))
    {
        return nullptr;
    }

    const FAnimNotifyEvent* AnimNotifyEvent = AnimSequence->Notifies.FindByPredicate(
       [](const FAnimNotifyEvent& NotifyEvent)
       {
           return NotifyEvent.Notify.IsA<T>();
       });

    return Cast<T>(AnimNotifyEvent != nullptr ? AnimNotifyEvent->Notify : nullptr);
}
