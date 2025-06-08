// Learning project from Udemy course


#include "STUProjectile.h"

#include "DrawDebugHelpers.h"
#include "Components/STUWeaponFXComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnitConversion.h"


ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(5.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
    MovementComponent->InitialSpeed = 2'000.f;
    MovementComponent->ProjectileGravityScale = 0.f;

    WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>(TEXT("WeaponFXComponent"));
}

void ASTUProjectile::SetLaunchDirection(FVector Direction)
{
    LaunchDirection = MoveTemp(Direction);
}

void ASTUProjectile::OnProjectileHit(
    UPrimitiveComponent* HitComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    FVector NormalImpulse,
    const FHitResult& Hit)
{
    const auto* World = GetWorld();
    if (!IsValid(World))
    {
        return;
    }

    MovementComponent->StopMovementImmediately();

    // :TODO: make damage
    UGameplayStatics::ApplyRadialDamage(
        World,
        DamageAmount,
        GetActorLocation(),
        DamageRadius,
        UDamageType::StaticClass(),
        {GetOwner()},
        this,
        GetCauserController(),
        bDoFullDamage);

    WeaponFXComponent->PlayImpactFX(Hit);

    Destroy();
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

    check(IsValid(CollisionComponent));
    check(IsValid(MovementComponent));
    check(IsValid(WeaponFXComponent));

    CollisionComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnProjectileHit);
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);

    MovementComponent->Velocity = LaunchDirection * MovementComponent->InitialSpeed;
    SetLifeSpan(LifeSpan);
}

AController* ASTUProjectile::GetCauserController() const
{
    if (const auto* OwnerPawn = GetOwner<APawn>(); !IsValid(OwnerPawn))
    {
        return OwnerPawn->GetController();
    }

    return nullptr;
}
