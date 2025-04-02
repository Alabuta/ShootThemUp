// Learning project from Udemy course


#include "STUCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


ASTUCharacterBase::ASTUCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	// GetCharacterMovement()->bOrientRotationToMovement = true;
	//
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;
}

void ASTUCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ASTUCharacterBase::MoveForward(const float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ASTUCharacterBase::MoveRight(const float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ASTUCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTUCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ThisClass::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("TurnAround"), this, &ThisClass::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ThisClass::Jump);
}

