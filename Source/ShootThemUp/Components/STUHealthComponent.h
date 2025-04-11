// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "EditorMetadataOverrides.h"
#include "Components/ActorComponent.h"
#include "STUHealthComponent.generated.h"


class AController;
class UDamageType;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE(FOnDeath);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const float);

public:

	USTUHealthComponent();

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

    UFUNCTION(BlueprintPure, Category="Health")
    float GetHealth() const;

    UFUNCTION(BlueprintPure, Category="Health")
    bool IsDead() const { return CurrentHealth <= 0.f; }

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health", meta=(ClampMin="1", ClampMax="1000"))
    float MaxHealth{100.f};

	virtual void BeginPlay() override;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor,
        float Damage,
        const UDamageType* DamageType,
        AController* InstigatedBy,
        AActor* DamageCauser);

private:

    float CurrentHealth{0.f};
};

inline float USTUHealthComponent::GetHealth() const
{
    return CurrentHealth;
}
