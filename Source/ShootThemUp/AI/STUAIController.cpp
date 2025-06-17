// Learning project from Udemy course


#include "STUAIController.h"

#include "STUAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STUAIPerceptionComponent.h"


ASTUAIController::ASTUAIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>(TEXT("PerceptionComponent"));
    SetPerceptionComponent(*AIPerceptionComponent);
}

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

void ASTUAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    auto* ClosestEnemy = GetFocusOnActor();
    SetFocus(ClosestEnemy);
}

AActor* ASTUAIController::GetFocusOnActor() const
{
    const auto* BlackboardComponent = GetBlackboardComponent();
    if (!IsValid(BlackboardComponent))
    {
        return nullptr;
    }

    return Cast<AActor>(BlackboardComponent->GetValueAsObject(FocusOnKeyName));
}
