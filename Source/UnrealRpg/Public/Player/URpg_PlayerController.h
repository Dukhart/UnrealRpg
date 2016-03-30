// Copyright Jordan Duncan 2015 \\ Description=RPG Template
#pragma once

#include "GameFramework/PlayerController.h"

#include "URpg_PlayerCameraManager.h"

#include "URpg_PlayerController.generated.h"


// Input Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMove_Strafe, const FVector&, Direction, const float&, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FMove_ForwardBack, const FVector&, Direction, const float&, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLook_UpDown, const float&, value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLook_RightLeft, const float&, value);

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
	// called when our controller possess a new pawn
	virtual void Possess(APawn* InPawn) override;

public:
	// handles contruction that requires the player to be fully loaded
	UFUNCTION()
	virtual void RunPostLoginEvents();

protected:
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

public:
	// * DELEGATES * //
	// handles
	UPROPERTY(BlueprintAssignable, Category = Input)
	FMove_Strafe Move_Strafe;
	UPROPERTY(BlueprintAssignable, Category = Input)
	FMove_Strafe Move_ForwardBack;
	UPROPERTY(BlueprintAssignable, Category = Input)
	FLook_UpDown Look_UpDown;
	UPROPERTY(BlueprintAssignable, Category = Input)
	FLook_RightLeft Look_RightLeft;
	
protected:
	// * INPUT * //
	// Detect Character Movement Input on the X axis (Left / Right)
	UFUNCTION()
	virtual void MoveStrafe(float value);
	// Detect Character Movement Input on the Y axis (Forward / Back)
	UFUNCTION()
	virtual void MoveForwardBack(float value);
	// Detect Jump Input
	UFUNCTION()
	virtual void MoveJump(float value);
	// Detect Camera Movement Input on the Y Axis
	UFUNCTION()
	virtual void LookUpDownRate(float value);
	UFUNCTION()
	virtual void LookUpDown(float value);
	// Detect Camera Movement Input on the X Axis
	UFUNCTION()
	virtual void LookRightLeftRate(float value);
	UFUNCTION()
	virtual void LookRightLeft(float value);

public:
	// * CAMERA * //
	// Switch between Controller/Camera styles
	UFUNCTION(BlueprintCallable, Category = Camera)
		virtual void ActivateCameraMode(ECameraMode newCameraMode);
	// Attach the Camera to the Pawns camera Boom
	// returns true if attach occured
	// returns false if it failed
	UFUNCTION(BlueprintCallable, Category = Camera)
		bool AttachCameraToOwnedCharacter();
private:
	// Activates First Person Camera Mode
	UFUNCTION()
	virtual void ActivateFirstPersonCamera();
	// Activates Over the Shoulder Camera Mode
	UFUNCTION()
	virtual void ActivateOverShoulderCamera();
	// Activates Free Range Camera Mode
	UFUNCTION()
	virtual void ActivateFreeRangeCamera();
	// Activates Sky View Camera Mode
	UFUNCTION()
	virtual void ActivateSkyViewCamera();
	// Detaches camera and controls from player character, operates like a spectator
	UFUNCTION()
	virtual void ActivateFreeCamera();

public:
	// * GETTERS AND SETTERS * //
	UFUNCTION(BlueprintCallable, Category = Camera)
	ECameraMode GetCameraMode() const {
		if (PlayerCameraManager != nullptr) {
			AURpg_PlayerCameraManager* camManRef = Cast<AURpg_PlayerCameraManager>(PlayerCameraManager);
			if (camManRef != nullptr) {
				return camManRef->GetCameraMode();
			}
		}
		return ECameraMode::None;
	};
};
