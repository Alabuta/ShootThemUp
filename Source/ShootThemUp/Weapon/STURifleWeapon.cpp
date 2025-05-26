// Learning project from Udemy course


#include "STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Components/STUWeaponFXComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/Engine.h"
#include "Engine/HitResult.h"
#include "GameFramework/PlayerController.h"


ASTURifleWeapon::ASTURifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>(TEXT("WeaponFXComponent"));
}

void ASTURifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(IsValid(WeaponFXComponent));
}

void ASTURifleWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ThisClass::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

TPair<FVector, FVector> ASTURifleWeapon::GetTracePoints(const APlayerController* PlayerController) const
{
    const auto [PlayerViewPointLocation, PlayerViewPointRotation] = GetPlayerViewPoint(PlayerController);

    const auto TraceStart = PlayerViewPointLocation;
    const auto ShotDirection = FMath::VRandCone(
        PlayerViewPointRotation.Vector(),
        FMath::DegreesToRadians(BulletSpread));
    const auto TraceEnd = TraceStart + ShotDirection * 10'000.f;

    return TPair<FVector, FVector>{TraceStart, TraceEnd};
}

void ASTURifleWeapon::MakeShot()
{
    if (IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    const auto* World = GetWorld();
    if (!IsValid(World))
    {
        return;
    }

    const auto* PlayerController = GetPlayerController();
    if (!IsValid(PlayerController))
    {
        return;
    }

    const auto [TraceStart, TraceEnd] = GetTracePoints(PlayerController);
    const auto HitResult = Trace(TraceStart, TraceEnd);

    if (!HitResult)
    {
        StopFire();
        return;
    }

    const auto MuzzleSocketLocation = GetMuzzleWorldLocation();

    if (!HitResult->bBlockingHit)
    {
        DrawDebugLine(
            World,
            MuzzleSocketLocation,
            TraceEnd,
            FColor::Red,
            false,
            3.f,
            0,
            2.f
        );

        return;
    }

    WeaponFXComponent->PlayImpactFX(*HitResult);

    MakeDamage(*HitResult);

    DecreaseAmmo();

    /*DrawDebugLine(
        World,
        MuzzleSocketLocation,
        HitResult->ImpactPoint,
        FColor::Red,
        false,
        3.f,
        0,
        2.f);

    DrawDebugSphere(
        World,
        HitResult->ImpactPoint,
        10.f,
        24,
        FColor::Orange,
        false,
        5.f);

    GEngine->AddOnScreenDebugMessage(
        -1,
        5.f,
        FColor::Red,
        FString::Printf(TEXT("Bone: %s"), *HitResult->BoneName.ToString()));*/
}

void ASTURifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    auto* DamagedActor = HitResult.GetActor();
    if (!IsValid(DamagedActor))
    {
        return;
    }

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
