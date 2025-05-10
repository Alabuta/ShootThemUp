// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUWeaponBase.generated.h"


USTRUCT(BlueprintType)
struct FSTUAmmoData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    int32 Bullets{0};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon", meta=(EditCondition="!bInfinite"))
    int32 Clips{0};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    uint8 bInfinite : 1{false};
};

UCLASS(Abstract)
class SHOOTTHEMUP_API ASTUWeaponBase : public AActor
{
    GENERATED_BODY()

public:

    ASTUWeaponBase();

    virtual void StartFire() PURE_VIRTUAL(ASTUWeaponBase::StartFire,);
    virtual void StopFire() PURE_VIRTUAL(ASTUWeaponBase::StopFire,);

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

    UPROPERTY(VisibleDefaultsOnly, Category="Components")
    FName MuzzleSocketName{TEXTVIEW("MuzzleSocket")};

    UPROPERTY(EditDefaultsOnly, Category="Weapon")
    FSTUAmmoData DefaultAmmoData{15, 10, false};

    virtual void BeginPlay() override;

    APlayerController* GetPlayerController() const;
    FVector GetMuzzleWorldLocation() const;
    virtual TPair<FVector, FVector> GetTracePoints(const APlayerController* PlayerController) const;

    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;

    virtual void MakeShot() PURE_VIRTUAL(ASTUWeaponBase::MakeShot,);

    TOptional<FHitResult> Trace(const FVector& TraceStart, const FVector& TraceEnd) const;

    void DecreaseAmmo();
    void ChangeClip();
    void LogAmmo();

    static TPair<FVector, FRotator> GetPlayerViewPoint(const APlayerController* PlayerController);

private:

    FSTUAmmoData CurrentAmmoData;
};

inline bool ASTUWeaponBase::IsAmmoEmpty() const
{
    return !CurrentAmmoData.bInfinite && CurrentAmmoData.Clips == 0 && IsClipEmpty();
}

inline bool ASTUWeaponBase::IsClipEmpty() const
{
    return CurrentAmmoData.Bullets == 0;
}
