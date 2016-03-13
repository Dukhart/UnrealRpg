// Copyright Jordan Duncan 2015 \\ Description=RPG Template
#pragma once

#include "GameFramework/PlayerController.h"

#include "URpg_PlayerCameraManager.h"

#include "URpg_PlayerController.generated.h"

UCLASS()
class UNREALRPG_API AURpg_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// * INTITIALIZATION * //
	// Constructor
	AURpg_PlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// Called after the constructor
	// World and component dependent starting behavior should go here
	virtual void BeginPlay() override;
	// Binds user inpur to functions
	virtual void SetupInputComponent() override;

	// * SETTINGS * //
	// rate at wich the pawn will turn
	float baseTurnRate;
	// rate at wich the camera will move
	float baseLookRate;
	// inverts Y axis camera movment if true
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		bool bInvertLookYAxis;
	// inverts X axis camera movment if true
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Controls)
		bool bInvertLookXAxis;
	// used by the animator to detect pawn movement in the X axis (X axis being the local pawn X not the world X)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float MoveValX;
	// used by the animator to detect pawn movement in the Y axis (Y axis being the local pawn Y not the world Y)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
		float MoveValY;

	// * EVENTS * //
	DECLARE_EVENT_OneParam(AURpg_PlayerController, FMove_Strafe, const float&);
	FMove_Strafe& OnMove_Strafe() { return Move_Strafe; }
private:
	// Event handles
	FMove_Strafe Move_Strafe;

protected:
	// * INPUT * //
	// Detect Character Movement Input on the X axis (Left / Right)
	virtual void MoveStrafe(float value);
	// Detect Character Movement Input on the Y axis (Forward / Back)
	virtual void MoveForwardBack(float value);
	// Detect Jump Input
	virtual void MoveJump(float value);
	// Detect Camera Movement Input on the Y Axis
	virtual void LookUpDownRate(float value);
	virtual void LookUpDown(float value);
	// Detect Camera Movement Input on the X Axis
	virtual void LookRightLeftRate(float value);
	virtual void LookRightLeft(float value);

public:
	// * CAMERA * //
	// Switch between Controller/Camera styles
	UFUNCTION(BlueprintCallable, Category = Camera)
		virtual void ActivateCameraMode(ECameraMode newCameraMode);
private:
	// Activates First Person Camera Mode
	virtual void ActivateFirstPersonCamera();
	// Activates Over the Shoulder Camera Mode
	virtual void ActivateOverShoulderCamera();
	// Activates Free Range Camera Mode
	virtual void ActivateFreeRangeCamera();
	// Activates Sky View Camera Mode
	virtual void ActivateSkyViewCamera();
	// Detaches camera and controls from player character, operates like a spectator
	virtual void ActivateFreeCamera();

	// * GETTERS AND SETTERS * //

};
