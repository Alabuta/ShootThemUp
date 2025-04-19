// Learning project from Udemy course


#include "STUGameHUD.h"

#include "Engine/Canvas.h"


void ASTUGameHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawCrosshair();
}

void ASTUGameHUD::DrawCrosshair()
{
    const int32 CenterX = Canvas->SizeX / 2.f;
    const int32 CenterY = Canvas->SizeY / 2.f;

    constexpr float HalfLineSize = 10.f;
    constexpr float LineThickness = 2.f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(CenterX - HalfLineSize, CenterY, CenterX + HalfLineSize, CenterY, LineColor, LineThickness);
    DrawLine(CenterX, CenterY - HalfLineSize, CenterX, CenterY + HalfLineSize, LineColor, LineThickness);
}
