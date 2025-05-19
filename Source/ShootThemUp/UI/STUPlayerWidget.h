// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerWidget.generated.h"


struct FSTUWeaponUIData;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerWidget : public UUserWidget
{
	GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure, Category="UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintPure, Category="UI")
    bool GetWeaponUIData(FSTUWeaponUIData& UIData) const;
};
