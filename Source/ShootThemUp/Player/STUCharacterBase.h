// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUCharacterBase.generated.h"


class UCameraComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:

	ASTUCharacterBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
