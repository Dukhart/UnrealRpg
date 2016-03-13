// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#pragma once


#include "URpg_PlayerCharacter.generated.h"

UCLASS()
class UNREALRPG_API AURpg_PlayerCharacter : public ACharacter
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

protected:
	// * INTITIALIZATION * //
	// constructor
	// add components and set default values
	AURpg_PlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// called after the constructor
	// world and component dependent starting behavior should go here
	virtual void BeginPlay() override;

public:
	// * GETTERS AND SETTERS * //
	// Returns CameraBoom subobject
	UFUNCTION(BlueprintCallable, Category = Camera)
	class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	// Returns FollowCamera subobject
	UFUNCTION(BlueprintCallable, Category = Camera)
	class UCameraComponent* GetPlayerCamera() const { return PlayerCamera; }
};
