// Copyright Jordan Duncan 2015

#include "UnrealRpg.h"
#include "URpg_CharacterMovementComponent.h"



// * INTITIALIZATION * //
// constructor
UURpg_CharacterMovementComponent::UURpg_CharacterMovementComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {

}
// * MOVEMENT * //
void UURpg_CharacterMovementComponent::AddInputVector(FVector WorldVector, bool bForce) {
	GEngine->AddOnScreenDebugMessage(30, 1, FColor::Green, " APPLYING MOVE: " + FString::SanitizeFloat(WorldVector.X) + ", " + FString::SanitizeFloat(WorldVector.Y) + ", " + FString::SanitizeFloat(WorldVector.Z));
	Super::AddInputVector(WorldVector, bForce);
}
// * ROTATION * //
// Sets the actor rotation to the input rotation
void UURpg_CharacterMovementComponent::SetRotation(const FRotator& newRotation) {
	if (GetPawnOwner() != nullptr) {
		GetPawnOwner()->SetActorRotation(newRotation);
		SERVER_RequestSet_Rotation(newRotation);
	}
}
// adds the input rotation to the actors current rotation
void UURpg_CharacterMovementComponent::AddRotation(const FRotator& newRotation) {
	if (GetPawnOwner() != nullptr) {
		GetPawnOwner()->SetActorRotation(newRotation + GetPawnOwner()->GetActorRotation());
	}
}

// request to the server to update rotation
void UURpg_CharacterMovementComponent::SERVER_RequestSet_Rotation_Implementation(const FRotator& newRotation) {
	if (GetPawnOwner() != nullptr) {
		GetPawnOwner()->SetActorRotation(newRotation);
	}
}
bool UURpg_CharacterMovementComponent::SERVER_RequestSet_Rotation_Validate(const FRotator& newRotation) {
	return true;
}