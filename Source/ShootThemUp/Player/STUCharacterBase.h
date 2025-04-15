// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCharacterBase.generated.h"


class UTextRenderComponent;
class USTUHealthComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

    explicit ASTUCharacterBase(const FObjectInitializer& ObjectInitializer);

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintPure, Category="Movement")
    bool GetIsRunning() const;

    UFUNCTION(BlueprintPure, Category="Movement")
    float GetMovementDirectionAngle() const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    TObjectPtr<USTUHealthComponent> HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    TObjectPtr<UTextRenderComponent> HealthRenderComponent;

    UPROPERTY(EditDefaultsOnly, Category="Animation")
    TObjectPtr<UAnimMontage> DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category="Animation")
    FVector2D LandedDamageSpeed{900.f, 1200.f};

    UPROPERTY(EditDefaultsOnly, Category="Animation")
    FVector2D LandedDamage{10.f, 100.f};

    virtual void BeginPlay() override;

    UFUNCTION()
    void OnGroundLanded(const FHitResult& HitResult);

private:

    uint8 bMovingForward : 1 {false};
    uint8 bRequiredRunning : 1 {false};

	void MoveForward(const float Value);
	void MoveRight(const float Value);

	void OnStartRunning();
	void OnStopRunning();

    void OnDeath();
    void OnHealthChanged(const float CurrentHealth);
};
