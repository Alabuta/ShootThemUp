// Learning project from Udemy course


#include "STUGameModeBase.h"

#include "ShootThemUp/Player/STUCharacterBase.h"
#include "ShootThemUp/Player/STUPlayerController.h"
#include "ShootThemUp/UI/STUGameHUD.h"


ASTUGameModeBase::ASTUGameModeBase()
{
	DefaultPawnClass = ASTUCharacterBase::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
    HUDClass = ASTUGameHUD::StaticClass();
}
