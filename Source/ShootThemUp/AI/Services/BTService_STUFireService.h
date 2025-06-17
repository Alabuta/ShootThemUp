// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_STUFireService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UBTService_STUFireService : public UBTService
{
	GENERATED_BODY()

public:

    UBTService_STUFireService();

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

    void TickNodeInternal(UBehaviorTreeComponent& OwnerComp) const;
};
