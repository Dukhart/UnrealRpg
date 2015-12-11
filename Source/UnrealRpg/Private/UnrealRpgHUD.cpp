// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "UnrealRpgHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"



AUnrealRpgHUD::AUnrealRpgHUD() {
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTextureObj(*FURLs::DefaultCrosshiarTexture);
	CrosshiarText = CrosshiarTextureObj.Object;
}

void AUnrealRpgHUD::DrawHUD() {
	Super::DrawHUD();
	// Get players current camera mode
	ECameraMode eCurrentCameraMode = Cast<AUnrealRpgPlayerCameraManager>(GetOwningPlayerController()->PlayerCameraManager)->GetCameraMode();

	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	FVector2D DrawPosition;
	switch (eCurrentCameraMode)
	{
	case ECameraMode::FirstPerson:
		// Draw the crosshiar in the center of the screen
		DrawPosition.X = Center.X - (CrosshiarText->GetSurfaceWidth() * 0.5f);
		DrawPosition.Y = Center.Y - (CrosshiarText->GetSurfaceHeight() * 0.5f);
		break;
	default:
		break;
	}
}