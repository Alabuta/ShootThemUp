// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "STUPickupItemBase.h"
#include "STUHealthPickupItem.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickupItem : public ASTUPickupItemBase
{
	GENERATED_BODY()

protected:

    virtual bool GivePickupItemTo(APawn* Pawn) override;
};
