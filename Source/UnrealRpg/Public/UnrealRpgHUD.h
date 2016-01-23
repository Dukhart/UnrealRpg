// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "GameFramework/HUD.h"
#include "UnrealRpgHUD.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API AUnrealRpgHUD : public AHUD
{
	GENERATED_BODY()
public:
	AUnrealRpgHUD(const FObjectInitializer& ObjectInitializer);
	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;
public:
	// HUD TEXTURE elements
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HUDTextures)
		TAssetPtr<UTexture2D> CrosshiarTexture;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Statusbars)
		TAssetPtr<UTexture2D> HealthBarTexture;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Statusbars)
		TAssetPtr<UTexture2D> StaminaBarTexture;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Statusbars)
		TAssetPtr<UTexture2D> ManaBarTexture;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Statusbars)
		TAssetPtr<UTexture2D> StatusBarBackgroundTexture;

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
	// DELEGATES for Change texture request completion
	void DoAsyncChangeCrosshair();
	
	bool loadingBasicTextures;
	void LoadBasicPlayerHUDTextures(TArray<FString> tPaths);
	void FinishedLoadBasicPlayerHUDTextures(FString name);

	bool LoadTexture2D(FString tPath);
	void DoAsyncLoadTexture2D(FString tPath);

};
