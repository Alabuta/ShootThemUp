// Learning project from Udemy course


#include "STUDevDamageActor.h"

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


ASTUDevDamageActor::ASTUDevDamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);
}

void ASTUDevDamageActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASTUDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    DrawDebugSphere(
        GetWorld(),
        GetActorLocation(),
        Radius,
        24,
        Color,
        false,
        -1.f,
        0,
        1.f
    );

    UGameplayStatics::ApplyRadialDamage(
        GetWorld(),
        Damage,
        GetActorLocation(),
        Radius,
        nullptr,
        {},
        this,
        nullptr,
        bDoFullDamage
    );
}

