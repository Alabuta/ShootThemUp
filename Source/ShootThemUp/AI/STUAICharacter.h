// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "STUCharacterBase.h"
#include "STUAICharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAICharacter : public ASTUCharacterBase
{
	GENERATED_BODY()

public:

    explicit ASTUAICharacter(const FObjectInitializer& ObjectInitializer);
};
