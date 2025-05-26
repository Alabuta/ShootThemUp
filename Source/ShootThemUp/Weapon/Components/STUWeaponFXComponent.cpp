// Learning project from Udemy course


#include "Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

#include "Engine/HitResult.h"
#include "Engine/World.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        ImpactFX,
        HitResult.ImpactPoint,
        HitResult.ImpactNormal.Rotation());
}

void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
}
