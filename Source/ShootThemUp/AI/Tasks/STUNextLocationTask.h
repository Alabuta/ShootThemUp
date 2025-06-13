// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "STUNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUNextLocationTask : public UBTTaskNode
{
    GENERATED_BODY()

public:

    USTUNextLocationTask();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float Radius{1000.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector AimLocationKey;

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; 
};
