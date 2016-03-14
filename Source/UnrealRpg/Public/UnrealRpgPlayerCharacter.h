// Copyright Jordan Duncan 2015 \\

#pragma once

#include "UnrealRpgCharacter.h"
#include "UnrealRpgPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API AUnrealRpgPlayerCharacter : public AUnrealRpgCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;
public:
	AUnrealRpgPlayerCharacter();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface
public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetPlayerCamera() const { return PlayerCamera; }
};