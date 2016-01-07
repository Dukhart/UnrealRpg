// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "UnrealRpgHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"



AUnrealRpgHUD::AUnrealRpgHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTextureObj(*FURLs::DefaultCrosshiarTexture);
	CrosshiarText = CrosshiarTextureObj.Object;
}
// will handle loading texture2D assets at runtime so we don't have to load them all at the same time in the header
UTexture2D* AUnrealRpgHUD::LoadTexture2D(FString tPath) {
	FStreamableManager* stream = new FStreamableManager;
	//Get a refrence to the object based on th input string
	FStringAssetReference ref(tPath);
	//Load the object through the StreamableManager and cast it to a Texture2D as it will return a UObject
	return Cast<UTexture2D>(stream->SynchronousLoad(ref));
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