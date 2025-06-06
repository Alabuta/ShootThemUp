// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShootThemUp/PickupItems/STUHealthPickupItem.h"
#include "STUHealthComponent.generated.h"


class UCameraShakeBase;
class AController;
class UDamageType;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

    DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
    DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, const float, const float);

public:

	USTUHealthComponent();

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;

    UFUNCTION(BlueprintPure, Category="Health")
    float GetHealth() const;

    UFUNCTION(BlueprintPure, Category="Health")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintPure, Category="Health")
    bool IsDead() const;

    bool TryAddHealth(const float HealthAmount);

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    TSubclassOf<UCameraShakeBase> CameraShakeOnDamage;

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
    bool IsHealthFull() const;

private:

    FTimerHandle HealthTimerHandle;

    float CurrentHealth{0.f};

    void HealUpdate();
    void SetHealth(const float NewHealth);

    void PlayCameraShake();
};

inline float USTUHealthComponent::GetHealth() const
{
    return CurrentHealth;
}

inline float USTUHealthComponent::GetHealthPercent() const
{
    return CurrentHealth / MaxHealth;
}

inline bool USTUHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(CurrentHealth, MaxHealth);
}
