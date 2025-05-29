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

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    FSTUImpactFXData DefaultImpactFXData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    TMap<TObjectPtr<UPhysicalMaterial>, FSTUImpactFXData> ImpactFXDataMap;

	virtual void BeginPlay() override;
};
