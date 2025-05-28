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
    UNiagaraSystem* ImpactFX = DefaultImpactFX;
    
    if (HitResult.PhysMaterial.IsValid())
    {
        if (const auto* FoundImpactFX = ImpactFXMap.Find(HitResult.PhysMaterial.Get());
            FoundImpactFX != nullptr && IsValid(*FoundImpactFX))
        {
            ImpactFX = *FoundImpactFX;
        }
    }
    
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
