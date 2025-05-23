// Learning project from Udemy course


#include "STUPickupItemBase.h"

#include "TimerManager.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Pawn.h"
#include "Logging/StructuredLog.h"


ASTUPickupItemBase::ASTUPickupItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
    CollisionComponent->InitSphereRadius(50.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASTUPickupItemBase::BeginPlay()
{
	Super::BeginPlay();

    check(IsValid(CollisionComponent));

    GenerateRotationYaw();
}

void ASTUPickupItemBase::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    if (auto* Pawn = Cast<APawn>(OtherActor); GivePickupItemTo(Pawn))
    {
        PickupItemWasTaken();
    }
}

bool ASTUPickupItemBase::GivePickupItemTo(APawn* Pawn)
{
    return false;
}

void ASTUPickupItemBase::PickupItemWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ThisClass::Respawn, RespawnTime);
}

void ASTUPickupItemBase::Respawn()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);

    GenerateRotationYaw();
}

void ASTUPickupItemBase::GenerateRotationYaw()
{
    RotationYaw = FMath::RandRange(-2.f, 2.f);
}

void ASTUPickupItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorWorldRotation(FRotator{0.f, RotationYaw, 0.f});
}
