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

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category="Components")
    TObjectPtr<UProjectileMovementComponent> MovementComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DamageRadius{200.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float DamageAmount{50.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float LifeSpan{5.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    uint8 bDoFullDamage : 1{false};

    UFUNCTION()
    void OnProjectileHit(
        UPrimitiveComponent* HitComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        FVector NormalImpulse,
        const FHitResult& Hit);

	virtual void BeginPlay() override;

private:

    FVector LaunchDirection;

    AController* GetCauserController() const;
};
