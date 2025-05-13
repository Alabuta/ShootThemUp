// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimSequenceBase.h"
#include "Animation/AnimNotifies/AnimNotify.h"


class FTUAnimUtils
{
public:

    template <class T>
    static T* FindFirstAnimNotify(const UAnimSequenceBase* AnimSequence)
    {
        if (!IsValid(AnimSequence))
        {
            return nullptr;
        }

        const FAnimNotifyEvent* AnimNotifyEvent = AnimSequence->Notifies.FindByPredicate(
           [](const FAnimNotifyEvent& NotifyEvent)
           {
               return NotifyEvent.Notify.IsA<T>();
           });

        return Cast<T>(AnimNotifyEvent != nullptr ? AnimNotifyEvent->Notify : nullptr);
    }
};