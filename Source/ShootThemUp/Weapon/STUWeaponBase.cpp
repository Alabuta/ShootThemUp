// Learning project from Udemy course


#include "STUWeaponBase.h"

#include "DrawDebugHelpers.h"
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

void ASTUWeaponBase::BeginPlay()
{
	Super::BeginPlay();
    check(IsValid(SkeletalMeshComponent));

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
    CurrentAmmoData.Bullets = FMath::Max(CurrentAmmoData.Bullets - 1, 0);
    LogAmmo();

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        ChangeClip();
    }
}

void ASTUWeaponBase::ChangeClip()
{
    CurrentAmmoData.Bullets = DefaultAmmoData.Bullets;

    if (!CurrentAmmoData.bInfinite)
    {
        CurrentAmmoData.Clips = FMath::Max(CurrentAmmoData.Clips - 1, 0);
    }

    UE_LOGFMT(LogSTUBaseWeapon, Display, "Clip changed! Clips left: {0}", CurrentAmmoData.Clips);
}

void ASTUWeaponBase::LogAmmo()
{
    const auto AmmoInfo = FString::Printf(
        TEXT("Ammo: %d/%d"),
        CurrentAmmoData.Bullets,
        CurrentAmmoData.bInfinite ? -1 : CurrentAmmoData.Clips);
    UE_LOGFMT(LogSTUBaseWeapon, Display, "{0}", *AmmoInfo);
}

TPair<FVector, FRotator> ASTUWeaponBase::GetPlayerViewPoint(const APlayerController* PlayerController)
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
