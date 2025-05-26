// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "STUWeaponBase.h"
#include "STURifleWeapon.generated.h"

class USTUWeaponFXComponent;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUWeaponBase
{
    GENERATED_BODY()

public:

    ASTURifleWeapon();

    virtual void BeginPlay() override;

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TObjectPtr<USTUWeaponFXComponent> WeaponFXComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(Units="Seconds"))
    float TimeBetweenShots{.1f};

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(Units="Degrees"))
    float BulletSpread{1.5f};

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float DamageAmount{10.f};

    virtual TPair<FVector, FVector> GetTracePoints(const APlayerController* PlayerController) const override;

    virtual void MakeShot() override;

private:

    FTimerHandle ShotTimerHandle;

    void MakeDamage(const FHitResult& HitResult);
};
