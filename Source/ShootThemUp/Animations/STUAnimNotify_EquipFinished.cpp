// Learning project from Udemy course


#include "STUAnimNotify_EquipFinished.h"


void USTUAnimNotify_EquipFinished::Notify(
    USkeletalMeshComponent* MeshComp,
    UAnimSequenceBase* Animation,
    const FAnimNotifyEventReference& EventReference)
{
    OnNotified.Broadcast(MeshComp);

    Super::Notify(MeshComp, Animation, EventReference);
}
