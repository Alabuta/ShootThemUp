// Learning project from Udemy course


#include "STUAICharacter.h"

#include "STUAIController.h"


ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAIController::StaticClass();
}
