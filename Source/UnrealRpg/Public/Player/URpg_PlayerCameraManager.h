// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "URpg_PlayerCameraManager.generated.h"

// Different availible Camera modes
UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	FirstPerson, // standard first person camera with head bob options forr a more real feel.
	OverShoulder, // 3rd person camera locked in behind the player pawn 
	FreeRange, // Free moving camera locked in orbit around the player pawn (Similar to Darksouls or Batman Arkham games)
	SkyViewCamera, // Top down view center locked to player pawn (similar to Diablo or Torchlight)
	TacticalCamera, // Top down camera locked within a distance from the player pawn or pawns
	FreeCamera, // completely free moving camera with option ground and wall collision completely disconnected from player pawn (Similar to a spectator controller)

	None
};

UCLASS()
class UNREALRPG_API AURpg_PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
protected:
	// * INTITIALIZATION * //
	// Constructor
	AURpg_PlayerCameraManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// called after the constructor
	// world and component dependent starting behavior should go here
	virtual void BeginPlay() override;

	//bool fixedCamera;

private:
	// * SETTINGS * //
	// Current camera mode activated
	UPROPERTY(VisibleAnywhere, Category = CameraSettings)
		ECameraMode eCurrentCameraMode;
	// default camera mode to start on begin play
	// TODO: add load function that starts last used camera mode as default
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CameraSettings, meta = (AllowPrivateAccess = true))
		ECameraMode eDefaultCameraMode;

public:
	// * GETTERS AND SETTERS * //
	// Sets our camera mode
	UFUNCTION(BlueprintCallable, Category = CameraSettings)
		virtual void SetCameraMode(ECameraMode newCameraMode) { eCurrentCameraMode = newCameraMode; }
	// gets our camera mode
	UFUNCTION(BlueprintCallable, Category = CameraSettings)
		virtual ECameraMode GetCameraMode() const { return eCurrentCameraMode; }

};
