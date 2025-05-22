// Learning project from Udemy course


#include "STUHealthPickupItem.h"

#include "GameFramework/Pawn.h"


bool ASTUHealthPickupItem::GivePickupItemTo(APawn* Pawn)
{
    if (!IsValid(Pawn))
    {
        return false;
    }
    
    return true;
}
