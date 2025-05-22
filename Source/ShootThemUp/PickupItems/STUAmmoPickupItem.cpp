// Learning project from Udemy course


#include "STUAmmoPickupItem.h"

#include "GameFramework/Pawn.h"


bool ASTUAmmoPickupItem::GivePickupItemTo(APawn* Pawn)
{
    if (!IsValid(Pawn))
    {
        return false;
    }

    return true;
}
