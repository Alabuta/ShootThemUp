// Learning project from Udemy course


#include "STULauncherWeapon.h"

#include "STUProjectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


void ASTULauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTULauncherWeapon::StopFire()
{
}

void ASTULauncherWeapon::MakeShot()
{
    if (!IsValid(ProjectileClass))
    {
        return;
    }

    auto* World = GetWorld();
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

    const auto EndPoint = HitResult ? HitResult->ImpactPoint : TraceEnd;
    const auto LaunchDirection = (EndPoint - GetMuzzleWorldLocation()).GetSafeNormal();

    const FTransform SpawnTransform{FRotator::ZeroRotator, GetMuzzleWorldLocation()};
    auto* Projectile = World->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);

    if (Projectile == nullptr)
    {
        return;
    }

    Projectile->SetLaunchDirection(LaunchDirection);
    Projectile->FinishSpawning(SpawnTransform);
}
