// Copyright Jordan Duncan 2015 \\

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "UnrealRpgPlayerCameraManager.generated.h"

// Different availible Camera modes
UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	FirstPerson, // standard first person camera with head bob options forr a more real feel.
	OverShoulder, // 3rd person camera locked in behind the player pawn 
	FreeRange, // Free moving camera locked in orbit around the player pawn (Similar to Darksouls or Batman Arkham games)
	SkyViewCamera, // Top down view center locked to player pawn (similar to Diablo or Torchlight)
	TacticalCamera, // Top down camera locked within a distance from the player pawn or pawns
	FreeCamera // completely free moving camera with option ground and wall collision completely disconnected from player pawn (Similar to a spectator controller)
};

UCLASS()
class UNREALRPG_API AURpg_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AURpg_PlayerCameraManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	bool fixedCamera;
	virtual void SetCameraMode(ECameraMode newCameraMode);
	UFUNCTION(BlueprintCallable, Category = CameraSettings)
	virtual ECameraMode GetCameraMode();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CameraSettings)
	ECameraMode eCurrentCameraMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSettings)
	ECameraMode eDefaultCameraMode;
	virtual void BeginPlay() override;
};
