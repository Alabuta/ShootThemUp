// Learning project from Udemy course


#include "Components/STUWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Engine/HitResult.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"


USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
    auto ImpactFXData = DefaultImpactFXData;

    if (HitResult.PhysMaterial.IsValid())
    {
        if (const auto* FoundImpactFXData = ImpactFXDataMap.Find(HitResult.PhysMaterial.Get());
            FoundImpactFXData != nullptr && IsValid(FoundImpactFXData->NiagaraSystem))
        {
            ImpactFXData = *FoundImpactFXData;
        }
    }
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(),
        ImpactFXData.NiagaraSystem,
        HitResult.ImpactPoint,
        HitResult.ImpactNormal.Rotation());

    auto* DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(),
        ImpactFXData.DecalData.Material,
        ImpactFXData.DecalData.Size,
        HitResult.ImpactPoint,
        HitResult.ImpactNormal.Rotation());

    if (IsValid(DecalComponent))
    {
        DecalComponent->SetFadeOut(ImpactFXData.DecalData.LifeTime, ImpactFXData.DecalData.FadeOutTime);
    }
}

void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
}
