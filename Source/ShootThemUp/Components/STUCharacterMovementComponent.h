// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

    virtual float GetMaxSpeed() const override;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Run", meta=(ClampMin="1.1", ClampMax="10."))
    float RunModifier{2.f};
};
