// Learning project from Udemy course


#include "STUProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Math/UnitConversion.h"


ASTUProjectile::ASTUProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    CollisionComponent->InitSphereRadius(5.f);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComponent"));
    MovementComponent->InitialSpeed = 2'000.f;
    MovementComponent->ProjectileGravityScale = 0.f;
}

void ASTUProjectile::SetLaunchDirection(FVector Direction)
{
    LaunchDirection = MoveTemp(Direction);
}

void ASTUProjectile::BeginPlay()
{
	Super::BeginPlay();

    check(IsValid(CollisionComponent));
    check(IsValid(MovementComponent));

    MovementComponent->Velocity = LaunchDirection * MovementComponent->InitialSpeed;
    SetLifeSpan(5.f);
}
