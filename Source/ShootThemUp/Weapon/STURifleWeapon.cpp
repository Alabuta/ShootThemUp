// Learning project from Udemy course


#include "STURifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "TimerManager.h"
#include "Components/STUWeaponFXComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/Engine.h"
#include "Engine/HitResult.h"
#include "GameFramework/PlayerController.h"
#include "NiagaraComponent.h"


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
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ThisClass::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void ASTURifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
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

    const auto TraceEndPoint = HitResult->bBlockingHit
                                   ? HitResult->ImpactPoint
                                   : TraceEnd;

    if (HitResult->bBlockingHit)
    {
        WeaponFXComponent->PlayImpactFX(*HitResult);

        MakeDamage(*HitResult);
    }

    const auto MuzzleSocketLocation = GetMuzzleWorldLocation();
    WeaponFXComponent->SpawnTraceFX(MuzzleSocketLocation, TraceEndPoint);

    DecreaseAmmo();
}

void ASTURifleWeapon::InitMuzzleFX()
{
    if (!IsValid(MuzzleFXComponent))
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    SetMuzzleFXVisibility(true);
}

void ASTURifleWeapon::SetMuzzleFXVisibility(const bool bVisible) const
{
    if (IsValid(MuzzleFXComponent))
    {
        MuzzleFXComponent->SetPaused(!bVisible);
        MuzzleFXComponent->SetVisibility(bVisible, true);
    }
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
