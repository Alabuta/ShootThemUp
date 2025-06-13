// Learning project from Udemy course


#include "STUAIController.h"

#include "STUAICharacter.h"


void ASTUAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto* AICharacter = Cast<ASTUAICharacter>(InPawn);
    if (!IsValid(AICharacter))
    {
        return;
    }

    RunBehaviorTree(AICharacter->GetBehaviorTree());
}
