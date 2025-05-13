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

    DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
    DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, const float);

public:

	USTUHealthComponent();

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintPure, Category="Health")
    float GetHealth() const;

    UFUNCTION(BlueprintPure, Category="Health")
    bool IsDead() const;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health", meta=(ClampMin="1", ClampMax="1000"))
    float MaxHealth{100.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Heal", meta=(Units="Seconds", EditCondition="bAutoHeal"))
    float HealUpdateTime{1.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Heal", meta=(Units="Seconds", EditCondition="bAutoHeal"))
    float HealStartDelay{3.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Heal", meta=(EditCondition="bAutoHeal"))
    float HealAmount{5.f};

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Heal")
    uint8 bAutoHeal : 1 {true};

	virtual void BeginPlay() override;

    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor,
        float Damage,
        const UDamageType* DamageType,
        AController* InstigatedBy,
        AActor* DamageCauser);

private:

    FTimerHandle HealthTimerHandle;

    float CurrentHealth{0.f};

    void HealUpdate();
    void SetHealth(const float NewHealth);
};

inline float USTUHealthComponent::GetHealth() const
{
    return CurrentHealth;
}
