// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUWeaponBase.generated.h"


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

    virtual void BeginPlay() override;

    APlayerController* GetPlayerController() const;
    FVector GetMuzzleWorldLocation() const;
    virtual TPair<FVector, FVector> GetTracePoints(const APlayerController* PlayerController) const;

    virtual void MakeShot() PURE_VIRTUAL(ASTUWeaponBase::MakeShot,);

    TOptional<FHitResult> Trace(const FVector& TraceStart, const FVector& TraceEnd) const;

    static TPair<FVector, FRotator> GetPlayerViewPoint(const APlayerController* PlayerController);
};
