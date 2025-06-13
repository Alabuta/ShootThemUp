// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "STUCharacterBase.h"
#include "STUAICharacter.generated.h"

class UBehaviorTree;
/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUCharacterBase
{
	GENERATED_BODY()

public:

    explicit ASTUAICharacter(const FObjectInitializer& ObjectInitializer);

    UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    TObjectPtr<UBehaviorTree> BehaviorTree;
};
