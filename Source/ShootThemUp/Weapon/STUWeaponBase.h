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

    virtual void Fire();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

    UPROPERTY(VisibleDefaultsOnly, Category="Components")
    FName MuzzleSocketName{TEXTVIEW("MuzzleSocket")};

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float DamageAmount{10.f};

    virtual void BeginPlay() override;

    void MakeShot();

private:

    APlayerController* GetPlayerController() const;
    FVector GetMuzzleWorldLocation() const;

    TOptional<FHitResult> Trace(const FVector& TraceStart, const FVector& TraceEnd) const;
    void MakeDamage(const FHitResult& HitResult);

    static TPair<FVector, FRotator> GetPlayerViewPoint(const APlayerController* PlayerController);
    static TPair<FVector, FVector> GetTracePoints(const APlayerController* PlayerController);
};
