// Learning project from Udemy course


#include "STUWeaponBase.h"

#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "STUCharacterBase.h"
#include "TimerManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY_STATIC(LogSTUBaseWeapon, All, All);

ASTUWeaponBase::ASTUWeaponBase()
{
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName{TEXTVIEW("SkeletalMeshComponent")});
    SetRootComponent(SkeletalMeshComponent);
    
	PrimaryActorTick.bCanEverTick = false;
}

bool ASTUWeaponBase::CanReload() const
{
    return CurrentAmmoData.Bullets < DefaultAmmoData.Bullets && CurrentAmmoData.Clips > 0;
}

void ASTUWeaponBase::ChangeClip()
{
    if (!CurrentAmmoData.bInfinite)
    {
        if (CurrentAmmoData.Clips <= 0)
        {
            UE_LOGFMT(LogSTUBaseWeapon, Display, "No clips left!");
            return;
        }

        CurrentAmmoData.Clips = FMath::Max(CurrentAmmoData.Clips - 1, 0);
    }

    CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;

    UE_LOGFMT(LogSTUBaseWeapon, Display, "Clip changed! Clips left: {0}", CurrentAmmoData.Clips);
}

bool ASTUWeaponBase::TryAddAmmo(const int32 ClipsAmount)
{
    if (CurrentAmmoData.bInfinite || IsAmmoFull() || ClipsAmount <= 0)
    {
        return false;
    }

    if (IsAmmoEmpty())
    {
        CurrentAmmoData.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmoData.Clips + 1);
        OnClipEmpty.Broadcast(this);
    }
    else if (CurrentAmmoData.Clips < DefaultAmmoData.Clips)
    {
        if (const auto NextClipsAmount = CurrentAmmoData.Clips + ClipsAmount;
            DefaultAmmoData.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmoData.Clips = NextClipsAmount;
        }
        else
        {
            CurrentAmmoData.Clips = DefaultAmmoData.Clips;
            CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;
        }
    }
    else
    {
        CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;
    }

    return true;
}

void ASTUWeaponBase::BeginPlay()
{
	Super::BeginPlay();

    check(IsValid(SkeletalMeshComponent));
    checkf(DefaultAmmoData.Bullets > 0, TEXT("Bullets count must be greater than 0!"));
    checkf(DefaultAmmoData.Clips > 0, TEXT("Clips count must be greater than 0!"));

    CurrentAmmoData = DefaultAmmoData;
}

APlayerController* ASTUWeaponBase::GetPlayerController() const
{
    const auto* OwnerCharacter = GetOwner<ACharacter>();
    if (!IsValid(OwnerCharacter))
    {
        return nullptr;
    }

    return OwnerCharacter->GetController<APlayerController>();
}

FVector ASTUWeaponBase::GetMuzzleWorldLocation() const
{
    return SkeletalMeshComponent->GetSocketLocation(MuzzleSocketName);
}

TPair<FVector, FVector> ASTUWeaponBase::GetTracePoints(const APlayerController* PlayerController) const
{
    const auto [PlayerViewPointLocation, PlayerViewPointRotation] = GetPlayerViewPoint(PlayerController);

    const auto TraceStart = PlayerViewPointLocation;
    const auto TraceEnd = TraceStart + PlayerViewPointRotation.Vector() * 10'000.f;

    return TPair<FVector, FVector>{TraceStart, TraceEnd};
}

TOptional<FHitResult> ASTUWeaponBase::Trace(const FVector& TraceStart, const FVector& TraceEnd) const
{
    const auto* World = GetWorld();
    if (!IsValid(World))
    {
        return {};
    }

    FHitResult HitResult;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.bReturnPhysicalMaterial = true;

    World->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECollisionChannel::ECC_Visibility,
        QueryParams);

    return HitResult;
}

void ASTUWeaponBase::DecreaseAmmo()
{
    if (CurrentAmmoData.Bullets <= 0)
    {
        UE_LOGFMT(LogSTUBaseWeapon, Display, "Clip is empty!");
        return;
    }

    CurrentAmmoData.Bullets = FMath::Max(CurrentAmmoData.Bullets - 1, 0);

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

UNiagaraComponent* ASTUWeaponBase::SpawnMuzzleFX() const
{
    if (!MuzzleFX)
    {
        UE_LOGFMT(LogSTUBaseWeapon, Warning, "Muzzle FX is not set for weapon: {0}", *GetNameSafe(this));
        return nullptr;
    }

    auto* MuzzleFXComponent = UNiagaraFunctionLibrary::SpawnSystemAttached(
        MuzzleFX,
        SkeletalMeshComponent,
        MuzzleSocketName,
        FVector::ZeroVector,
        FRotator::ZeroRotator,
        EAttachLocation::SnapToTarget,
        true);

    return MuzzleFXComponent;
}

TPair<FVector, FRotator> ASTUWeaponBase::GetPlayerViewPoint(const APlayerController* PlayerController) const
{
    const auto* OwnerCharacter = GetOwner<ASTUCharacterBase>();
    if (!IsValid(OwnerCharacter))
    {
        return {};
    }

    if (OwnerCharacter->IsPlayerControlled())
    {
        if (!IsValid(PlayerController))
        {
            return {};
        }

        FVector PlayerViewPointLocation;
        FRotator PlayerViewPointRotation;

        PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

        return TPair<FVector, FRotator>{PlayerViewPointLocation, PlayerViewPointRotation};
    }

    return TPair<FVector, FRotator>{
        GetMuzzleWorldLocation(),
        SkeletalMeshComponent->GetSocketRotation(MuzzleSocketName)};

}
