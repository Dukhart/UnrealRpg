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
	AUnrealRpgHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = HUDTextures)
	class UTexture2D* CrosshiarText;
	
};
