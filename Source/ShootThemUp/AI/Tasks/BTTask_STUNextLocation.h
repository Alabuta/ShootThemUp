// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_STUNextLocation.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UBTTask_STUNextLocation : public UBTTaskNode
{
    GENERATED_BODY()

public:

    UBTTask_STUNextLocation();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector AimLocationKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI", meta=(EditCondition="!bSelfCenter"))
    FBlackboardKeySelector CenterActorKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float Radius{1000.f};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    uint8 bSelfCenter : 1{true};

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override; 
};
