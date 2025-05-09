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

    virtual void BeginPlay() override;
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

    UPROPERTY(EditDefaultsOnly, Category="Animation")
    TObjectPtr<UAnimMontage> EquipAnimMontage;

private:

    UPROPERTY(Transient)
    ASTUWeaponBase* CurrentWeapon{nullptr};

    UPROPERTY(Transient)
    TArray<ASTUWeaponBase*> Weapons;

    int32 CurrentWeaponIndex{0};

    uint8 bIsEquipInProgress : 1{false};

    bool CanFire() const;
    bool CanEquip() const;

    void SpawnWeapons();
    void EquipWeapon(const int32 WeaponIndex);
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);

    void InitAnimations();
    void PlayAnimMontage(UAnimMontage* AnimMontage) const;

    static void AttachWeaponToSocket(ASTUWeaponBase* Weapon, USceneComponent* AttachComponent, FName SocketName);
};
