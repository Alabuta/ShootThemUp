// Learning project from Udemy course


#include "STUWeaponBase.h"

#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
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

    const auto* OwnerCharacter = GetOwner<ACharacter>();
    if (!IsValid(OwnerCharacter))
    {
        return;
    }
    
    const auto* PlayerController = OwnerCharacter->GetController<APlayerController>();
    if (!IsValid(PlayerController))
    {
        return;
    }

    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

    const auto TraceStart = PlayerViewPointLocation;
    const auto TraceEnd = TraceStart + PlayerViewPointRotation.Vector() * 10'000.f;

    FHitResult HitResult;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(OwnerCharacter);

    World->LineTraceSingleByChannel(
        HitResult,
        TraceStart,
        TraceEnd,
        ECollisionChannel::ECC_Visibility,
        QueryParams);

    const auto MuzzleSocketTransform = SkeletalMeshComponent->GetSocketTransform(MuzzleSocketName);

    if (!HitResult.bBlockingHit)
    {
        DrawDebugLine(
            World,
            MuzzleSocketTransform.GetLocation(),
            TraceEnd,
            FColor::Red,
            false,
            3.f,
            0,
            2.f
        );

        return;
    }

    DrawDebugLine(
        World,
        MuzzleSocketTransform.GetLocation(),
        HitResult.ImpactPoint,
        FColor::Red,
        false,
        3.f,
        0,
        2.f);

    DrawDebugSphere(
        World,
        HitResult.ImpactPoint,
        10.f,
        24,
        FColor::Orange,
        false,
        5.f);

    GEngine->AddOnScreenDebugMessage(
        -1,
        5.f,
        FColor::Red,
        FString::Printf(TEXT("Bone: %s"), *HitResult.BoneName.ToString()));
}
