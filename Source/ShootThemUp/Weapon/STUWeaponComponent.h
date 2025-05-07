// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "STUWeaponComponent.generated.h"


class ASTUWeaponBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USTUWeaponComponent();

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void StartFire();
    void StopFire();
    void NextWeapon();

protected:

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TArray<TSubclassOf<ASTUWeaponBase>> WeaponClasses;

    UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
    FName WeaponEquipSocketName{TEXTVIEW("RightWeaponSocket")};

    UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
    FName WeaponArmorySocketName{TEXTVIEW("ArmorySocket")};

    virtual void BeginPlay() override;

private:

    UPROPERTY(Transient)
    ASTUWeaponBase* CurrentWeapon{nullptr};

    UPROPERTY(Transient)
    TArray<ASTUWeaponBase*> Weapons;

    int32 CurrentWeaponIndex{0};

    void SpawnWeapons();
    void EquipWeapon(const int32 WeaponIndex);

    static void AttachWeaponToSocket(ASTUWeaponBase* Weapon, USceneComponent* AttachComponent, FName SocketName);
};
