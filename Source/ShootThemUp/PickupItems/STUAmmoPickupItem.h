// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "STUPickupItemBase.h"
#include "STUAmmoPickupItem.generated.h"

class ASTUWeaponBase;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickupItem : public ASTUPickupItemBase
{
	GENERATED_BODY()

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickupItem", meta=(ClampMin="1", ClampMax="1000"))
    int32 ClipsAmount{10};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickupItem")
    TSubclassOf<ASTUWeaponBase> WeaponType;

    virtual bool GivePickupItemTo(APawn* Pawn) override;
};
