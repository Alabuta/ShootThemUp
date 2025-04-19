// Learning project from Udemy course


#include "STUWeaponBase.h"

#include "Components/SkeletalMeshComponent.h"
#include "Engine/Engine.h"


ASTUWeaponBase::ASTUWeaponBase()
{
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName{TEXTVIEW("SkeletalMeshComponent")});
    SetRootComponent(SkeletalMeshComponent);
    
	PrimaryActorTick.bCanEverTick = false;
}

void ASTUWeaponBase::Fire()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString{TEXTVIEW("Fire!")});
}

void ASTUWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}
