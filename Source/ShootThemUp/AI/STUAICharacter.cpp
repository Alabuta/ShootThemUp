// Learning project from Udemy course


#include "STUAICharacter.h"

#include "STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"


ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ASTUAIController::StaticClass();

    bUseControllerRotationYaw = false;

    if (auto* MovementComponent = GetCharacterMovement(); IsValid(MovementComponent))
    {
        MovementComponent->bUseControllerDesiredRotation = true;
        MovementComponent->RotationRate = FRotator(0.f, 0.f, 200.f);
    }
}
