// Learning project from Udemy course


#include "STUCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ShootThemUp/Components/STUCharacterMovementComponent.h"


ASTUCharacterBase::ASTUCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
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

    PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ThisClass::OnStartRunning);
    PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &ThisClass::OnStopRunning);
}

bool ASTUCharacterBase::GetIsRunning() const
{
    return bRequiredRunning && bMovingForward && !GetVelocity().IsZero();
}

float ASTUCharacterBase::GetMovementDirectionAngle() const
{
    const auto Velocity = GetVelocity().GetSafeNormal();
    if (Velocity.IsNearlyZero())
    {
        return 0.f;
    }

    const auto ActorForwardVector = GetActorForwardVector();

    const auto Y = ActorForwardVector.Cross(Velocity).Dot(GetActorUpVector());
    const auto X = Velocity.Dot(ActorForwardVector);

	return FMath::Atan2(Y, X);
}

void ASTUCharacterBase::MoveForward(const float Value)
{
    bMovingForward = Value > 0.f;
    AddMovementInput(GetActorForwardVector(), Value);
}

void ASTUCharacterBase::MoveRight(const float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ASTUCharacterBase::OnStartRunning()
{
    bRequiredRunning = true;
}

void ASTUCharacterBase::OnStopRunning()
{
    bRequiredRunning = false;
}
