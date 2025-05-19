// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "STUWeaponComponent.generated.h"


struct FSTUWeaponUIData;
class ASTUWeaponBase;


USTRUCT(BlueprintType)
struct FSTUWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<ASTUWeaponBase> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TObjectPtr<UAnimMontage> ReloadAnimMontage;
};


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
    void Reload();

    bool GetWeaponUIData(FSTUWeaponUIData& UIData) const;

protected:

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    TArray<FSTUWeaponData> WeaponData;

    UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
    FName WeaponEquipSocketName{TEXTVIEW("RightWeaponSocket")};

    UPROPERTY(VisibleDefaultsOnly, Category="Weapon")
    FName WeaponArmorySocketName{TEXTVIEW("ArmorySocket")};

    UPROPERTY(EditDefaultsOnly, Category="Animation")
    TObjectPtr<UAnimMontage> EquipAnimMontage;

private:

    static constexpr int32 WeaponNum{2};

    UPROPERTY(Transient)
    ASTUWeaponBase* CurrentWeapon{nullptr};

    UPROPERTY(Transient)
    UAnimMontage* CurrentReloadAnimMontage{nullptr};

    UPROPERTY(Transient)
    TArray<ASTUWeaponBase*> Weapons;

    int32 CurrentWeaponIndex{0};

    uint8 bIsEquipInProgress : 1{false};
    uint8 bIsReloadInProgress : 1{false};

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;

    void SpawnWeapons();
    void EquipWeapon(const int32 WeaponIndex);
    void ChangeClip();

    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

    void OnEmptyClip();

    void InitAnimations();
    void PlayAnimMontage(UAnimMontage* AnimMontage) const;

    static void AttachWeaponToSocket(ASTUWeaponBase* Weapon, USceneComponent* AttachComponent, FName SocketName);
};
