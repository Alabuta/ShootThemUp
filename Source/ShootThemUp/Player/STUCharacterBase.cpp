// Learning project from Udemy course


#include "STUCharacterBase.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/STUWeaponComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Logging/StructuredLog.h"
#include "ShootThemUp/Components/STUCharacterMovementComponent.h"
#include "ShootThemUp/Components/STUHealthComponent.h"
#include "ShootThemUp/Weapon/STUWeaponBase.h"


DEFINE_LOG_CATEGORY_STATIC(LogSTUCharacterBase, All, All);


ASTUCharacterBase::ASTUCharacterBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.f, 100.0f, 80.f);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>(TEXT("HealthComponent"));
    if (IsValid(HealthComponent))
    {
        HealthComponent->OnDeath.AddUObject(this, &ThisClass::OnDeath);
        HealthComponent->OnHealthChanged.AddUObject(this, &ThisClass::OnHealthChanged);
    }

    LandedDelegate.AddDynamic(this, &ThisClass::OnGroundLanded);

    HealthRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("HealthRenderComponent"));
    HealthRenderComponent->SetupAttachment(GetRootComponent());
    HealthRenderComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>(TEXT("USTUWeaponComponent"));

	// GetCharacterMovement()->bOrientRotationToMovement = true;
	//
	// bUseControllerRotationYaw = false;
	// bUseControllerRotationRoll = false;
}

void ASTUCharacterBase::BeginPlay()
{
	Super::BeginPlay();

    if (IsValid(HealthComponent))
    {
        OnHealthChanged(HealthComponent->GetHealth());
    }
}

void ASTUCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTUCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(PlayerInputComponent != nullptr);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ThisClass::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("TurnAround"), this, &ThisClass::AddControllerYawInput);

    PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ThisClass::Jump);

    PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &ThisClass::OnStartRunning);
    PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &ThisClass::OnStopRunning);

    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ThisClass::StartFireWeapon);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Released, this, &ThisClass::StopFireWeapon);

    PlayerInputComponent->BindAction(TEXT("NextWeapon"), IE_Pressed, this, &ThisClass::NextWeapon);

    PlayerInputComponent->BindAction(TEXT("Reload"), IE_Pressed, this, &ThisClass::Reload);
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

void ASTUCharacterBase::OnDeath()
{
    UE_LOGFMT(LogSTUCharacterBase, Warning, "Character %s is dead! [{0}]", *GetNameSafe(this));

    if (auto* MovementComponent = GetCharacterMovement(); IsValid(MovementComponent))
    {
        MovementComponent->DisableMovement();
    }

    if (IsValid(WeaponComponent))
    {
        WeaponComponent->StopFire();
    }

    SetLifeSpan(5.f);

    if (IsValid(Controller))
    {
        Controller->ChangeState(NAME_Spectating);
    }

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

    if (auto* SkeletalMeshComponent = GetMesh(); IsValid(SkeletalMeshComponent))
    {
        SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        SkeletalMeshComponent->SetSimulatePhysics(true);
    }
}

void ASTUCharacterBase::OnHealthChanged(const float CurrentHealth)
{
    if (IsValid(HealthRenderComponent) && IsValid(HealthComponent))
    {
        HealthRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), CurrentHealth)));
    }
}

void ASTUCharacterBase::OnGroundLanded(const FHitResult& HitResult)
{
    const auto* MovementComponent = GetCharacterMovement();
    const auto FallSpeed = FMath::Abs(MovementComponent->Velocity.  Z);

    if (FallSpeed < LandedDamageSpeed.X)
    {
        return;
    }

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(
        LandedDamageSpeed,
        LandedDamage,
        FallSpeed
    );

    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ASTUCharacterBase::StartFireWeapon()
{
    if (!IsValid(WeaponComponent))
    {
        return;
    }

    WeaponComponent->StartFire();
}

void ASTUCharacterBase::StopFireWeapon()
{
    if (!IsValid(WeaponComponent))
    {
        return;
    }

    WeaponComponent->StopFire();
}

void ASTUCharacterBase::NextWeapon()
{
    if (!IsValid(WeaponComponent))
    {
        return;
    }

    WeaponComponent->NextWeapon();
}

void ASTUCharacterBase::Reload()
{
    if (!IsValid(WeaponComponent))
    {
        return;
    }

    WeaponComponent->Reload();
}
