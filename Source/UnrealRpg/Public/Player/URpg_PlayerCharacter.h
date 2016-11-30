// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once

// include to use our custom camera manager
#include "URpg_PlayerCameraManager.h"
// include to use our custom movement component
#include "URpg_CharacterMovementComponent.h"
// include the custom base character class
#include "URpg_Character.h"
// UI //
// include to add UI widgets
#include "Runtime/UMG/Public/Components/WidgetComponent.h"
#include "URpg_HUD_UserWidget.h"

#include "URpg_PlayerCharacter.generated.h"

UCLASS()
class UNREALRPG_API AURpg_PlayerCharacter : public AURpg_Character
{
	GENERATED_BODY()

private:
	// * COMPONENTS * //
	// Camera boom positioning the camera behind the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	// Follow camera 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UURpg_CharacterMovementComponent* MovementCompRef;
	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	ECameraMode eCurrentCameraMode;

	// * UMG * //
	// Used by other players to see current status of player if enabled
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI", meta = (AllowPrivateAccess = true))
		UWidgetComponent* StatusWidgetComp;
	// the instance of the status comp
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|UI", meta = (AllowPrivateAccess = true))
		UURpg_HUD_UserWidget* StatusWidgetInstance;
	

protected:
	// * INTITIALIZATION * //
	// constructor
	// add components and set default values
	AURpg_PlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// set replicated properties
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	// called after the constructor
	virtual void BeginPlay() override;
	// binds client input from the controller to the characters movement
	UFUNCTION(BlueprintCallable, Client, Reliable, Category = Input)
	void CLIENT_BindInputDelegates();
	void CLIENT_BindInputDelegates_Implementation();

public:
	// returns the movement component
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	// runs when a player first logs in
	UFUNCTION(BlueprintNativeEvent, Category = Spawn)
	void RunPostLoginEvents();
	// runs whenever the character is respawned
	UFUNCTION(BlueprintNativeEvent, Category = Spawn)
	void RunRespawnEvents();

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override;

protected:
	// * DESTRUCTION * //
	// extra end play behavior
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// * MOVEMENT * //
	// Detect Character Movement Input on the X axis (Left / Right)
	UFUNCTION()
	virtual void DoMoveStrafe(const FVector& Direction, const float& value);
	// Detect Character Movement Input on the Y axis (Forward / Back)
	UFUNCTION()
	virtual void DoMoveForwardBack(const FVector& Direction, const float& value);
	// Detect Jump Input
	UFUNCTION()
	virtual void DoMoveJump(float value);
	// Detect Camera Movement Input on the Y Axis
	UFUNCTION()
	virtual void DoLookUpDownRate(float value);
	UFUNCTION()
	virtual void DoLookUpDown(float value);
	// Detect Camera Movement Input on the X Axis
	UFUNCTION()
	virtual void DoLookRightLeftRate(float value);
	UFUNCTION()
	virtual void DoLookRightLeft(float value);

public:
	// * GETTERS AND SETTERS * //
	// Returns CameraBoom subobject
	UFUNCTION(BlueprintCallable, Category = Camera)
	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Returns FollowCamera subobject
	UFUNCTION(BlueprintCallable, Category = Camera)
	class UCameraComponent* GetPlayerCamera() const { return PlayerCamera; }

	// Asks the server what the players current camera mode is
	UFUNCTION(BlueprintCallable, Category = Camera)
	ECameraMode GetPlayersCameraMode();
	// returns characters camera mode from the server
	// since the player controller / camera manger only exists on the server and owning client this will allow camera replication
	// to all clients by accessing the camera state from the server
	UFUNCTION(Server, Reliable, WithValidation)
	void SERVER_RequestPlayerCameraMode();
};
