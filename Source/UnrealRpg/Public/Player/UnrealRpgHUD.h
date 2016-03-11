// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "GameFramework/HUD.h"
#include "UnrealRpgHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API AURpg_HUD : public AHUD
{
	GENERATED_BODY()
public:
	AURpg_HUD(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
public:
	// HUD TEXTURE elements
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDTextures)
		TAssetPtr<UTexture2D> CrosshiarTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statusbars)
		TAssetPtr<UTexture2D> HealthBarTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statusbars)
		TAssetPtr<UTexture2D> StaminaBarTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statusbars)
		TAssetPtr<UTexture2D> ManaBarTexture;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Statusbars)
		TAssetPtr<UTexture2D> StatusBarBackgroundTexture;

	
	// load texture 2D methods
	UTexture2D* LoadTexture2D(FString tPath);
	TArray<UTexture2D*> LoadMultipleTexture2D(TArray<FString> tPaths);

	bool LoadTexture2DPtr(TAssetPtr<UTexture2D> asset);
	// Change texture request methods
	bool ChangeCrosshair(int32 ID);
	bool ChangeCrosshair(FString ID);
	bool ChangeHealthBar(int32 ID);
	bool ChangeHealthBar(FString ID);
	bool ChangeStaminaBar(int32 ID);
	bool ChangeStaminaBar(FString ID);
	bool ChangeManaBar(int32 ID);
	bool ChangeManaBar(FString ID);
	bool ChangeStatusBarBackground(int32 ID);
	bool ChangeStatusBarBackground(FString ID);
private:
	// DELEGATES for load texture request completion
	//void DoAsyncLoadTexture2D(FString tPath);
	//void DoLoadMultipleTexture2D(TArray<FString> tPaths);
	// DELEGATES for Change texture request completion
	void DoLoadTexture2DPtr(TAssetPtr<UTexture2D> asset);
	void DoAsyncChangeCrosshair();
};
