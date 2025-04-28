// Learning project from Udemy course


#include "STUWeaponBase.h"

#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/DamageEvents.h"
#include "Engine/Engine.h"
#include "GameFramework/Character.h"


ASTUWeaponBase::ASTUWeaponBase()
{
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName{TEXTVIEW("SkeletalMeshComponent")});
    SetRootComponent(SkeletalMeshComponent);
    
	PrimaryActorTick.bCanEverTick = false;
}

void ASTUWeaponBase::Fire()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString{TEXTVIEW("Fire!")});

    MakeShot();
}

void ASTUWeaponBase::BeginPlay()
{
	Super::BeginPlay();
    check(IsValid(SkeletalMeshComponent));
}

void ASTUWeaponBase::MakeShot()
{
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

    MakeDamage(*HitResult);

    DrawDebugLine(
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
        FString::Printf(TEXT("Bone: %s"), *HitResult->BoneName.ToString()));
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

void ASTUWeaponBase::MakeDamage(const FHitResult& HitResult)
{
    auto* DamagedActor = HitResult.GetActor();
    if (!IsValid(DamagedActor))
    {
        return;
    }

    DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
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

TPair<FVector, FVector> ASTUWeaponBase::GetTracePoints(const APlayerController* PlayerController)
{
    const auto [PlayerViewPointLocation, PlayerViewPointRotation] = GetPlayerViewPoint(PlayerController);

    const auto TraceStart = PlayerViewPointLocation;
    const auto TraceEnd = TraceStart + PlayerViewPointRotation.Vector() * 10'000.f;

    return TPair<FVector, FVector>{TraceStart, TraceEnd};
}