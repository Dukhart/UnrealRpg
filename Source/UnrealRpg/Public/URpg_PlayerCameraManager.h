// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

#include "Camera/PlayerCameraManager.h"

#include "URpg_PlayerCameraManager.generated.h"

// Different availible Camera modes
UENUM(BlueprintType)
enum class ECameraMode : uint8
{
	// standard first person camera with head bob options forr a more real feel.
	FirstPerson, 
	// 3rd person camera locked in behind the player pawn 
	OverShoulder, 
	// Free moving camera locked in orbit around the player pawn (Similar to Darksouls or Batman Arkham games)
	FreeRange, 
	// Top down view center locked to player pawn (similar to Diablo or Torchlight)
	SkyViewCamera, 
	// Top down camera locked within a distance from the player pawn or pawns
	TacticalCamera, 
	// completely free moving camera with option ground and wall collision completely disconnected from player pawn (Similar to a spectator controller)
	FreeCamera, 

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

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//FTimerHandle InitCameraHandle;
	//UFUNCTION()
	//void InitCamInterval();
	

private:
	// * SETTINGS * //
	// Current camera mode activated
	UPROPERTY(Replicated, VisibleAnywhere, Category = CameraSettings)
		ECameraMode eCurrentCameraMode;
	// default camera mode to start on begin play
	// TODO: add load function that starts last used camera mode as default
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = CameraSettings, meta = (AllowPrivateAccess = true))
		ECameraMode eDefaultCameraMode;

public:

	UFUNCTION(NetMulticast, Reliable)
	void InitDefaultCameraMode();
	void InitDefaultCameraMode_Implementation();

	// * GETTERS AND SETTERS * //
	// Sets our camera mode
	UFUNCTION(BlueprintCallable, Category = CameraSettings)
		virtual void SetCameraMode(ECameraMode newCameraMode) { 
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ECameraMode"), true);
		if (EnumPtr != nullptr && HasNetOwner()) {
			GEngine->AddOnScreenDebugMessage(-1, 100, FColor::Black, GetName() + " ne mode " + GetOwningPlayerController()->GetName() + " " + EnumPtr->GetNameByIndex(static_cast<uint8>(newCameraMode)).ToString());
		}

		eCurrentCameraMode = newCameraMode; }
	// gets our camera mode
	UFUNCTION(BlueprintCallable, Category = CameraSettings)
		virtual ECameraMode GetCameraMode() const { return eCurrentCameraMode; }
	UFUNCTION(BlueprintCallable, Category = CameraSettings)
		virtual ECameraMode GetDefaultCameraMode() const { return eDefaultCameraMode; }

};
