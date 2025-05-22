// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "STUPickupItemBase.h"
#include "STUAmmoPickupItem.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickupItem : public ASTUPickupItemBase
{
	GENERATED_BODY()

protected:

    virtual bool GivePickupItemTo(APawn* Pawn) override;
};
