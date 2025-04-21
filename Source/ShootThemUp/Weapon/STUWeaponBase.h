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

    virtual void BeginPlay() override;

    void MakeShot();
};
