// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"
#include "URpg_HUD.h"
#include "Engine/Canvas.h"
#include "TextureResource.h"
#include "CanvasItem.h"
//includes for our custom classess
#include "URpg_PlayerCharacter.h"
#include "URpg_PlayerCameraManager.h"




AURpg_HUD::AURpg_HUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	//static ConstructorHelpers::FObjectFinder<UTexture2D> CrosshiarTextureObj(*FURLs::DefaultCrosshiarTexture);
	//CrosshiarText = CrosshiarTextureObj.Object;
}

UTexture2D* AURpg_HUD::LoadTexture2D(FString tPath) {
	UTexture2D* newTexture = new UTexture2D();
	FStringAssetReference ref(tPath);
	UURpg_GameInstance* UGI = Cast<UURpg_GameInstance>(GetGameInstance());
	// check that we succesfully grabbed the game instance
	if (UGI) {
		//UGI->AssetLoader->RequestAsyncLoad(ref, FStreamableDelegate::CreateUObject(this, &AUnrealRpgHUD::DoAsyncLoadTexture2D, tPath));
		newTexture = Cast<UTexture2D>(UGI->AssetLoader->SynchronousLoad(ref));
		return newTexture;
	}
	else {
		UE_LOG(DebugLog, Error, TEXT("Load Texture failed to find game instance"));
		// the UGI should ALWAYS exist so this should never get called
		checkNoEntry();
	}
	return newTexture;
}
TArray<UTexture2D*> AURpg_HUD::LoadMultipleTexture2D(TArray<FString> tPaths) {
	// create an array to hold the textures
	TArray<UTexture2D*> newTextures;
	// create the asset refrence variable to be used to temporarly hold the asset paths in a format the asset loader understands
	FStringAssetReference ref;
	// get the game instance as it has the global asset loader
	UURpg_GameInstance* UGI = Cast<UURpg_GameInstance>(GetGameInstance());
	if (UGI) {
		for (int32 i = 0; i < tPaths.Num(); ++i) {
			// add the texture paths to the asset refrence
			ref = FStringAssetReference(tPaths[i]);
			// load the asset with the global asset loader from the UGI and add them to the texture array
			newTextures.AddUnique(Cast<UTexture2D>(UGI->AssetLoader->SynchronousLoad(ref)));
		}
		// return the array after all textures have been cycled through for loading
		return newTextures;
	}
	else {
		UE_LOG(DebugLog, Error, TEXT("Load Multiple Texture failed to find game instance"));
		// the UGI should ALWAYS exist so this should never get called
		checkNoEntry();
	}
	return newTextures;
}

bool AURpg_HUD::LoadTexture2DPtr(TAssetPtr<UTexture2D> asset) {
	// make sure the imported asset can be loaded
	if (asset.IsNull())
	{
		return false;
	}
	// get the game instance
	UURpg_GameInstance* UGI = Cast<UURpg_GameInstance>(GetGameInstance());
	// make sure we successfully grabbed the game instance
	if (UGI) {
		FStringAssetReference ref(asset.ToStringReference());
		UGI->AssetLoader->RequestAsyncLoad(ref, FStreamableDelegate::CreateUObject(this, &AURpg_HUD::DoLoadTexture2DPtr, asset));
		return true;
	}
	else {
		UE_LOG(DebugLog, Error, TEXT("LoadTexture2DPtr failed to find game instance"))
		checkNoEntry();
	}
	return false;
}
void AURpg_HUD::DoLoadTexture2DPtr(TAssetPtr<UTexture2D> asset) {

}
void AURpg_HUD::DrawHUD() {
	Super::DrawHUD();
	// Get players current camera mode
	ECameraMode eCurrentCameraMode = Cast<AURpg_PlayerCameraManager>(GetOwningPlayerController()->PlayerCameraManager)->GetCameraMode();
	// Find the center of the canvas
	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	// create a variable to hold object draw positions
	FVector2D DrawPosition;
}
//Change Texture Requests
// Changes the Crosshair to a new one based on the number assigned to the crosshair image
bool AURpg_HUD::ChangeCrosshair(int32 ID) {
	return false;
}
// Changes the Crosshair to a new one based on the name assigned to the crosshair image
bool AURpg_HUD::ChangeCrosshair(FString ID) {
	return false;
}
// Changes the HealthBar to a new one based on the number assigned to the crosshair image
bool AURpg_HUD::ChangeHealthBar(int32 ID) {
	return false;
}
// Changes the HealthBar to a new one based on the name assigned to the crosshair image
bool AURpg_HUD::ChangeHealthBar(FString ID) {
	return false;
}
// Changes the StaminaBar to a new one based on the number assigned to the crosshair image
bool AURpg_HUD::ChangeStaminaBar(int32 ID) {
	return false;
}
// Changes the StaminaBar to a new one based on the name assigned to the crosshair image
bool AURpg_HUD::ChangeStaminaBar(FString ID) {
	return false;
}
// Changes the ManaBar to a new one based on the number assigned to the crosshair image
bool AURpg_HUD::ChangeManaBar(int32 ID) {
	return false;
}
// Changes the ManaBar to a new one based on the name assigned to the crosshair image
bool AURpg_HUD::ChangeManaBar(FString ID) {
	return false;
}
// Changes the StatusBar Background to a new one based on the number assigned to the crosshair image
bool AURpg_HUD::ChangeStatusBarBackground(int32 ID) {
	return false;
}
// Changes the StatusBarBackground to a new one based on the name assigned to the crosshair image
bool AURpg_HUD::ChangeStatusBarBackground(FString ID) {
	return false;
}
// DELEGATES for Change texture request completion
void AURpg_HUD::DoAsyncChangeCrosshair() {

}
