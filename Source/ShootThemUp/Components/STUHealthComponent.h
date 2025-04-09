// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"


class AController;
class UDamageType;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	USTUHealthComponent();

    float GetHealth() const;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health", meta=(ClampMin="1", ClampMax="1000"))
    float MaxHealth{100.f};

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor,
        float Damage,
        const UDamageType* DamageType,
        AController* InstigatedBy,
        AActor* DamageCauser);

	virtual void BeginPlay() override;

private:

    float CurrentHealth{0.f};
};

inline float USTUHealthComponent::GetHealth() const
{
    return CurrentHealth;
}
