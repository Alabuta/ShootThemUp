// Learning project from Udemy course


#include "STUGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"


void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

void ASTUGameHUD::BeginPlay()
{
    Super::BeginPlay();

    if (auto* PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass); IsValid(PlayerHUDWidget))
    {
        PlayerHUDWidget->AddToViewport();
    }
}
