// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUPickupItemBase.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUPickupItemBase : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTUPickupItemBase();

	virtual void Tick(float DeltaTime) override;

protected:

    UPROPERTY(VisibleAnywhere, Category="PickupItem")
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PickupItem")
    float RespawnTime{5.f};

	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual bool GivePickupItemTo(APawn* Pawn);

private:

    float RotationYaw{0.f};

    void PickupItemWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
