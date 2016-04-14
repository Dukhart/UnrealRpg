// Copyright Jordan Duncan 2015

#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "URpg_CharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UURpg_CharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
protected:
	// * INTITIALIZATION * //
	// constructor
	UURpg_CharacterMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	//virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
public:
	// * MOVEMENT * //
	virtual void AddInputVector(FVector WorldVector, bool bForce = false) override;
	// * ROTATION * //
	// Sets the actor rotation to the input rotation
	UFUNCTION(BlueprintCallable, Category = "Movement|Rotation")
	void SetRotation(const FRotator& newRotation);
	// adds the input rotation to the actors current rotation
	UFUNCTION(BlueprintCallable, Category = "Movement|Rotation")
	void AddRotation(const FRotator& newRotation);
	// request to the server to update rotation
	UFUNCTION(Server, Reliable, WithValidation)
		void SERVER_RequestSet_Rotation(const FRotator& newRotation);
	void SERVER_RequestSet_Rotation_Implementation(const FRotator& newRotation);
	bool SERVER_RequestSet_Rotation_Validate(const FRotator& newRotation);
};
