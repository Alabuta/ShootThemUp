// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCharacterBase.generated.h"


class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ASTUCharacterBase();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	virtual void BeginPlay() override;

private:

	void MoveForward(const float Value);
	void MoveRight(const float Value);
};
