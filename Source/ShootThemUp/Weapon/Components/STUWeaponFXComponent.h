// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootThemUp/STUCoreTypes.h"
#include "STUWeaponFXComponent.generated.h"


class UNiagaraSystem;
struct FHitResult;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class SHOOTTHEMUP_API USTUWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

    USTUWeaponFXComponent();

    void PlayImpactFX(const FHitResult& HitResult);
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX|Impacts")
    FSTUImpactFXData DefaultImpactFXData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX|Impacts")
    TMap<TObjectPtr<UPhysicalMaterial>, FSTUImpactFXData> ImpactFXDataMap;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX|Traces")
    TObjectPtr<UNiagaraSystem> TraceFXSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX|Traces")
    FName TraceTargetParamName{TEXTVIEW("TraceTarget")};

	virtual void BeginPlay() override;
};
