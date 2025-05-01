// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "STUWeaponBase.h"
#include "STULauncherWeapon.generated.h"

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
	
};
