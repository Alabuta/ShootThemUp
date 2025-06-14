// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STUAIController.generated.h"

class USTUAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAIController : public AAIController
{
	GENERATED_BODY()

    ASTUAIController();

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
    TObjectPtr<USTUAIPerceptionComponent> AIPerceptionComponent;

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;
};
