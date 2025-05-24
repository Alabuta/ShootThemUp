// Learning project from Udemy course

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

struct FSTUUtils
{
    template <class T>
    static T* GetPawnComponent(const APawn* Pawn)
    {
        if (!IsValid(Pawn))
        {
            return nullptr;
        }

        return Pawn->GetComponentByClass<T>();
    }
};
