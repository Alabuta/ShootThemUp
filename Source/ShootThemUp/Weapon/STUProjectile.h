// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"


class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTUProjectile();

    void SetLaunchDirection(FVector Direction);

protected:

    UPROPERTY(VisibleDefaultsOnly, Category="Components")
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(VisibleDefaultsOnly, Category="Components")
    TObjectPtr<UProjectileMovementComponent> MovementComponent;

	virtual void BeginPlay() override;

private:

    FVector LaunchDirection;
};
