// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STUAnimNotifyBase.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*)

/**
 * 
 */
UCLASS(Abstract)
class SHOOTTHEMUP_API USTUAnimNotifyBase : public UAnimNotify
{
	GENERATED_BODY()

public:

    FOnNotifiedSignature OnNotified;

    virtual void Notify(
        USkeletalMeshComponent* MeshComp,
        UAnimSequenceBase* Animation,
        const FAnimNotifyEventReference& EventReference) override;
};
