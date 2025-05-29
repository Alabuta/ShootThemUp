// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCoreTypes.generated.h"


class UNiagaraSystem;


USTRUCT(BlueprintType)
struct FSTUDecalData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    TObjectPtr<UMaterialInterface> Material;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    FVector Size{10.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    float LifeTime{5.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    float FadeOutTime{.7f};
};


USTRUCT(BlueprintType)
struct FSTUImpactFXData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    TObjectPtr<UNiagaraSystem> NiagaraSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    FSTUDecalData DecalData;
};
