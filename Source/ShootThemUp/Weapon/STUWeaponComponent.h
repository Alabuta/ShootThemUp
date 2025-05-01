// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUWeaponComponent.generated.h"


class ASTUWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USTUWeaponComponent();

    void StartFire();
    void StopFire();

protected:

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TSubclassOf<ASTUWeaponBase> WeaponClass;

    UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
    FName AttachSocketName{TEXTVIEW("RightWeaponSocket")};

    virtual void BeginPlay() override;

private:

    UPROPERTY(Transient)
    ASTUWeaponBase* CurrentWeapon{nullptr};

    void SpawnWeapon();
};
