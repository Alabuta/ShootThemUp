// Learning project from Udemy course


#include "Components/STUAIPerceptionComponent.h"

#include "AIController.h"
#include "FSTUUtils.h"
#include "Perception/AISense_Sight.h"
#include "ShootThemUp/Components/STUHealthComponent.h"


AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
    const auto* Controller = GetOwner<AAIController>();
    if (!IsValid(Controller))
    {
        return nullptr;
    }

    const auto Pawn = Controller->GetPawn();
    if (!IsValid(Pawn))
    {
        return nullptr;
    }

    TArray<AActor*> PerceivedActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);

    if (PerceivedActors.IsEmpty())
    {
        return nullptr;
    }

    auto ClosestDistanceSquared = std::numeric_limits<float>::max();
    AActor* ClosestActor = nullptr;

    for (AActor* PerceivedActor : PerceivedActors)
    {
        const auto* HealthComponent = PerceivedActor->GetComponentByClass<USTUHealthComponent>();
        if (!IsValid(HealthComponent) || HealthComponent->IsDead()) // :TODO: make a check for AI team
        {
            continue;
        }

        const auto DistanceSquared = FVector::DistSquared(Pawn->GetActorLocation(), PerceivedActor->GetActorLocation());
        if (DistanceSquared < ClosestDistanceSquared)
        {
            ClosestDistanceSquared = DistanceSquared;
            ClosestActor = PerceivedActor;
        }
    }

    return ClosestActor;
}
