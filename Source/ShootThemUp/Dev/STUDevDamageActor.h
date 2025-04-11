// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTUDevDamageActor();

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    TObjectPtr<USceneComponent> SceneComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageTypeClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor Color{FColor::Red};

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius{300.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage{10.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    uint8 bDoFullDamage : 1 {true};

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
};
