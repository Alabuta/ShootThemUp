// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerWidget.generated.h"


class USTUWeaponComponent;
struct FSTUAmmoData;
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
    bool GetCurrentWeaponUIData(FSTUWeaponUIData& UIData) const;

    UFUNCTION(BlueprintPure, Category="UI")
    bool GetCurrentWeaponAmmoData(FSTUAmmoData& AmmoData) const;

private:

    const USTUWeaponComponent* GetWeaponComponent() const; 
};
