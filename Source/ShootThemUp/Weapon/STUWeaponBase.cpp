// Learning project from Udemy course


#include "STUWeaponBase.h"

#include "Components/SkeletalMeshComponent.h"


ASTUWeaponBase::ASTUWeaponBase()
{
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(FName{TEXTVIEW("SkeletalMeshComponent")});
    SetRootComponent(SkeletalMeshComponent);
    
	PrimaryActorTick.bCanEverTick = false;
}

void ASTUWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}
