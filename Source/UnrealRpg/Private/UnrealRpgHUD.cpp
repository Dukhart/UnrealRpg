// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "UnrealRpgHUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"



AUnrealRpgHUD::AUnrealRpgHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	//loadingBasicTextures = false;
	//static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTextureObj(*FURLs::DefaultCrosshiarTexture);
	//CrosshiarText = CrosshiarTextureObj.Object;
}
//Change Texture Requests
// Changes the Crosshair to a new one based on the number assigned to the crosshair image
bool AUnrealRpgHUD::ChangeCrosshair(int32 ID) {
	return false;
}
// Changes the Crosshair to a new one based on the name assigned to the crosshair image
bool AUnrealRpgHUD::ChangeCrosshair(FString ID) {
	return false;
}
// Changes the HealthBar to a new one based on the number assigned to the crosshair image
bool AUnrealRpgHUD::ChangeHealthBar(int32 ID) {
	return false;
}
// Changes the HealthBar to a new one based on the name assigned to the crosshair image
bool AUnrealRpgHUD::ChangeHealthBar(FString ID) {
	return false;
}
// Changes the StaminaBar to a new one based on the number assigned to the crosshair image
bool AUnrealRpgHUD::ChangeStaminaBar(int32 ID) {
	return false;
}
// Changes the StaminaBar to a new one based on the name assigned to the crosshair image
bool AUnrealRpgHUD::ChangeStaminaBar(FString ID) {
	return false;
}
// Changes the ManaBar to a new one based on the number assigned to the crosshair image
bool AUnrealRpgHUD::ChangeManaBar(int32 ID) {
	return false;
}
// Changes the ManaBar to a new one based on the name assigned to the crosshair image
bool AUnrealRpgHUD::ChangeManaBar(FString ID) {
	return false;
}
// Changes the StatusBar Background to a new one based on the number assigned to the crosshair image
bool AUnrealRpgHUD::ChangeStatusBarBackground(int32 ID) {
	return false;
}
// Changes the StatusBarBackground to a new one based on the name assigned to the crosshair image
bool AUnrealRpgHUD::ChangeStatusBarBackground(FString ID) {
	return false;
}

bool AUnrealRpgHUD::LoadTexture2D(FString tPath) {
	return false;
}
// DELEGATES for Change texture request completion
void AUnrealRpgHUD::DoAsyncLoadTexture2D(FString path) {

}
void AUnrealRpgHUD::DoAsyncChangeCrosshair() {

}


// will handle loading texture2D assets at runtime so we don't have to load them all at the same time in the header
void AUnrealRpgHUD::LoadBasicPlayerHUDTextures(TArray<FString> tPaths) {
	//FStreamableManager* stream = new FStreamableManager;
	TArray<FStringAssetReference> refs;

	FString name("asd");

	UUnrealRpgGameInstance* UGI = Cast<UUnrealRpgGameInstance>(GetGameInstance());
	if (UGI) {
		for (int32 i = 0; i < tPaths.Num(); ++i) {
			// using add unique instead of just add since it would be pointless to load the same texture twice
			// shouldn't really have much effect but will prevent slow down from user error inputing the same texture multiple times
			refs.AddUnique(tPaths[i]);
		}
		UGI->AssetLoader->RequestAsyncLoad(refs, FStreamableDelegate::CreateUObject(this, &AUnrealRpgHUD::FinishedLoadBasicPlayerHUDTextures, name));
	}
	else {
		return;
	}
	//Get a refrence to the object based on th input string
	
	//Load the object through the StreamableManager and cast it to a Texture2D as it will return a UObject
	//return Cast<UTexture2D>(stream->SynchronousLoad(ref));
}
void AUnrealRpgHUD::FinishedLoadBasicPlayerHUDTextures(FString name) {
	UE_LOG(DebugLog, Warning, TEXT(" %s "), *name);
}

void AUnrealRpgHUD::DrawHUD() {
	Super::DrawHUD();
	// Get players current camera mode
	ECameraMode eCurrentCameraMode = Cast<AUnrealRpgPlayerCameraManager>(GetOwningPlayerController()->PlayerCameraManager)->GetCameraMode();
	// Find the center of the canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	// create a variable to hold object draw positions
	FVector2D DrawPosition;
	// Current camera mode may effect some HUD elements draw position
	switch (eCurrentCameraMode)
	{
	case ECameraMode::FirstPerson:
		// Draw the crosshiar in the center of the screen
		//DrawPosition.X = Center.X - (CrosshiarText->GetSurfaceWidth() * 0.5f);
		//DrawPosition.Y = Center.Y - (CrosshiarText->GetSurfaceHeight() * 0.5f);
		break;
	default:
		break;
	}
}