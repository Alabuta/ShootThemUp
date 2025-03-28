// Learning project from Udemy course


#include "STUCharacterBase.h"

#include "Camera/CameraComponent.h"


ASTUCharacterBase::ASTUCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(FName{TEXTVIEW("CameraComponent")});
	CameraComponent->SetupAttachment(GetRootComponent());
}

void ASTUCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASTUCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTUCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

