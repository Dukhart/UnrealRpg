// Copyright Jordan Duncan 2015 \\

#pragma once

#include "Camera/PlayerCameraManager.h"
#include "UnrealRpgPlayerCameraManager.generated.h"

// Different availible Camera modes
UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	FirstPerson,
	OverShoulder,
	FreeRange,
	SkyViewCamera,
	FreeCamera
};

UCLASS()
class UNREALRPG_API AUnrealRpgPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	AUnrealRpgPlayerCameraManager();
public:
	virtual void SetCameraMode(ECameraMode newCameraMode);
	virtual ECameraMode GetCurrentCameraMode();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = CameraSettings)
	ECameraMode eCurrentCameraMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CameraSettings)
	ECameraMode eDefaultCameraMode;
};
