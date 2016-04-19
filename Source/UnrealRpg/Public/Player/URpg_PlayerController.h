// Copyright Jordan Duncan 2015 \\ Description=RPG Template
#pragma once

#include "GameFramework/PlayerController.h"

#include "URpg_PlayerCameraManager.h"
// includes for our custom classes
#include "URpg_PlayerCharacter.h"
// includes for our custom widgets
#include "URpg_StatBox_UserWidget.h"
#include "URpg_StatBar_UserWidget.h"
#include "URpg_StatIcon_UserWidget.h"
#include "URpg_HUD_UserWidget.h"

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
	// handles replicated property behavior
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	// Called after the constructor
	// World and component dependent starting behavior should go here
	virtual void BeginPlay() override;
	// Binds user inpur to functions
	virtual void SetupInputComponent() override;
public:
	// called when our controller possess a new pawn
	virtual void Possess(APawn* InPawn) override;
	UFUNCTION(Client, Reliable)
		void CLIENT_RunPostLogin();
	void CLIENT_RunPostLogin_Implementation();
	UFUNCTION(Server, Reliable, WithValidation)
		void SERVER_RunPostLogin();
	void SERVER_RunPostLogin_Implementation();
	bool SERVER_RunPostLogin_Validate();
	// handles contruction that requires the player to be fully loaded
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Spawn)
		void RunPostLoginEvents();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Spawn)
		void RunRespawnEvents();

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
	// Current class of the character
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Player)
		TSubclassOf<AURpg_PlayerCharacter> CharacterClass;
	// is the character alive
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Status)
		bool bIsAlive;
	// bools used for spawning / death logic
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Spawn)
		bool bLockoutDeathNSpawning;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Spawn)
		bool bIsImmortal;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Spawn)
		bool bCanSpawn;
	// suicide timers
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float SuicideHeldTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
	float SuicideHoldTime;

	FTimerHandle Suicide_TimerHandle;

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
	// AXIS
	// Detect Character Movement Input on the X axis (Left / Right)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void MoveStrafe(float value);
	// Detect Character Movement Input on the Y axis (Forward / Back)
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void MoveForwardBack(float value);
	// Detect Jump Input
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void MoveJump(float value);
	// Detect Camera Movement Input on the Y Axis
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void LookUpDownRate(float value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void LookUpDown(float value);
	// Detect Camera Movement Input on the X Axis
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void LookRightLeftRate(float value);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void LookRightLeft(float value);

	// Suicide player if held and alive
	// Respawn the player if pressed when dead
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void OnRespawnSuicide_Press();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void OnRespawnSuicide_Release();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Input)
		void OnRespawnSuicide_Hold();


	// * REQUEST TO SERVER * //
	// request the server to kill the player
	UFUNCTION(Server, Reliable, WithValidation)
		void SERVER_KillPlayer(bool bOverrideImmortality = false);
	// request the server to respawn the player
	UFUNCTION(Server, Reliable, WithValidation)
		void SERVER_RespawnPlayer();



public:
	// * CAMERA * //
	// Switch between Controller/Camera styles
	UFUNCTION(BlueprintCallable, Category = Camera)
		virtual void ActivateCameraMode(ECameraMode newCameraMode, bool bForceActivate = false);
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

	// Components for the UI
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI", meta = (AllowPrivateAccess = true))
		UWidgetComponent* HUDComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI", meta = (AllowPrivateAccess = true))
		UURpg_HUD_UserWidget* HUDInstance;

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
	UFUNCTION(BlueprintCallable, Category = Status)
		bool GetIsAlive() {
		return bIsAlive;
	}
	// sets Alive status
	// requires authority should automaticly be replicated to client
	UFUNCTION(BlueprintCallable, Category = Status)
		void SetIsAlive(bool InStatus) {
		if (Role == ROLE_Authority) {
			bIsAlive = InStatus;
		}
	}
	// requires authority should automaticly be replicated to client
	UFUNCTION(BlueprintCallable, Category = Spawn)
		void SetLockoutDeathNSpawning(bool InStatus) {
		if (Role == ROLE_Authority) {
			bLockoutDeathNSpawning = InStatus;
		}
	}
	// requires authority should automaticly be replicated to client
	UFUNCTION(BlueprintCallable, Category = Spawn)
		void SetIsImmortal(bool InStatus) {
		if (Role == ROLE_Authority) {
			bIsImmortal = InStatus;
		}
	}
	// requires authority should automaticly be replicated to client
	UFUNCTION(BlueprintCallable, Category = Spawn)
		void SetCanSpawn(bool InStatus) {
		if (Role == ROLE_Authority) {
			bCanSpawn = InStatus;
		}
	}
	UFUNCTION(BlueprintCallable, Category = Spawn)
		bool GetLockoutDeathNSpawning() {
		return bLockoutDeathNSpawning;
	}
	UFUNCTION(BlueprintCallable, Category = Spawn)
		bool GetIsImmortal() {
		return bIsImmortal;
	}
	UFUNCTION(BlueprintCallable, Category = Spawn)
		bool GetCanSpawn() {
		return bCanSpawn;
	}

	TSubclassOf<AURpg_PlayerCharacter> GetCharacterClass() {
		return CharacterClass;
	}

	UFUNCTION(BlueprintCallable, Category = HUD)
		UWidgetComponent* GetHUDComp() const { return HUDComp; }
};
