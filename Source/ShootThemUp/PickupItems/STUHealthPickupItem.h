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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="PickupItem", meta=(ClampMin="1", ClampMax="100"))
    float HealthAmount{100};

    virtual bool GivePickupItemTo(APawn* Pawn) override;
};
