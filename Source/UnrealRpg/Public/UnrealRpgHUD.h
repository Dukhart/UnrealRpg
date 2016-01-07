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

	UTexture2D* LoadTexture2D(FString tPath);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HUDTextures)
	class UTexture2D* CrosshiarText;
	
};
