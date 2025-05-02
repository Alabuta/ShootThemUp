// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "STUWeaponBase.h"
#include "STULauncherWeapon.generated.h"

class ASTUProjectile;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUWeaponBase
{
    GENERATED_BODY()

public:

    virtual void StartFire() override;
    virtual void StopFire() override;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<ASTUProjectile> ProjectileClass;

    virtual void MakeShot() override;
};
