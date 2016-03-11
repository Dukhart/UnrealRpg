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
public:
	AUnrealRpgPlayerController(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	float baseTurnRate;
	float baseLookRate;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		bool bInvertLookYAxis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		bool bInvertLookXAxis;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float MoveValX; // used by the animator to detect pawn movement in the X axis (X axis being the local pawn X not the world X)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float MoveValY; // used by the animator to detect pawn movement in the Y axis (Y axis being the local pawn X not the world X)
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
	virtual void LookUpDownRate(float value);
	virtual void LookUpDown(float value);
	virtual void LookRightLeftRate(float value);
	virtual void LookRightLeft(float value);

};
