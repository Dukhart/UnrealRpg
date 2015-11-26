// Copyright Jordan Duncan 2015 \\

#pragma once

#include "GameFramework/PlayerController.h"
#include "UnrealRpgPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API AUnrealRpgPlayerController : public APlayerController
{
	GENERATED_BODY()
	AUnrealRpgPlayerController();
protected:
	virtual void SetupInputComponent() override;
	bool bInvertLookYAxis;
	bool bInvertLookXAxis;
	float baseTurnRate;
	float baseLookRate;
public:
	// Switch between Controller/Camera styles
	virtual void ActivateFirstPersonCamera();
	virtual void ActivateOverShoulderCamera();
	virtual void ActivateFreeRangeCamera();
	virtual void ActivateSkyViewCamera();
	// Detaches camera and controls from player character, operates like a spectator
	virtual void ActivateFreeCamera();


	// Detect Character Movement Input
	virtual void MoveStrafe(float value);
	virtual void MoveForwardBack(float value);
	virtual void MoveJump(float value);
	// Detect Camera Movement Input
	virtual void LookUpDown(float value);
	virtual void LookRightLeft(float value);

};
