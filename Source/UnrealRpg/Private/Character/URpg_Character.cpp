// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealRpg.h"
#include "URpg_Character.h"
// needed for replicated properties
#include "Net/UnrealNetwork.h"


// Sets default values
AURpg_Character::AURpg_Character(const FObjectInitializer& ObjectInitializer) 
	: Super (ObjectInitializer)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CharacterType = ECharacterType::None;
}

void AURpg_Character::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

		DOREPLIFETIME(AURpg_Character, Stats);
		DOREPLIFETIME(AURpg_Character, Attributes);
		DOREPLIFETIME(AURpg_Character, CharacterType);
		DOREPLIFETIME(AURpg_Character, Nickname);
}

// Called when the game starts or when spawned
void AURpg_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AURpg_Character::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AURpg_Character::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

// takes longer then by index as it will check ALL assigned stats for a matching name then update them
void AURpg_Character::SetStatValue_ByName(EStatName stat, float value, EAffectedProperty prop) {
	// iterate through the stored stats
	/*
	for (int32 i = 0; i < Stats.Num(); ++i) {
		// check if the name matches the desired stat
		if (Stats[i].StatName == stat) {
			// add the value to the stat at the index
			SetStatValue_ByIndex(i, value, prop);
		}
	}
	*/
	SetStatValue_ByIndex((uint8)stat, value, prop);
}
// faster then by name as it will go directly to the input index to update
void AURpg_Character::SetStatValue_ByIndex(uint8 statIndex, float value, EAffectedProperty prop) {
	// check the index is valid
	if (Stats.IsValidIndex(statIndex)) {
		// set the new value
		//Stats[statIndex].SetValue(value);

		switch (prop)
		{
		case EAffectedProperty::Base:
			Stats[statIndex].SetValue(value);
			break;
		case EAffectedProperty::Min:
			Stats[statIndex].SetMin(value);
			break;
		case EAffectedProperty::Max:
			Stats[statIndex].SetMax(value);
			break;
		case EAffectedProperty::Buff:
			Stats[statIndex].SetBuff(value);
			break;
		case EAffectedProperty::None:
			break;
		default:
			break;
		}

		// update the display widget
		UpdateStatWidget(Stats[statIndex].StatName);
	}
}
// takes longer then by index as it will check ALL assigned stats for a matching name then update them
void AURpg_Character::AddStatValue_ByName(EStatName stat, float value, EAffectedProperty prop) {
	// iterate through the stored stats
	/*
	for (int32 i = 0; i < Stats.Num(); ++i) {
		// check if the name matches the desired stat
		if (Stats[i].StatName == stat) {
			// add the value to the stat at the index
			AddStatValue_ByIndex(i, value, prop);
		}
	}
	*/
	AddStatValue_ByIndex((uint8)stat, value, prop);
}
// faster then by name as it will go directly to the input index to update
void AURpg_Character::AddStatValue_ByIndex(uint8 statIndex, float value, EAffectedProperty prop) {
	// check the index is valid
	if (Stats.IsValidIndex(statIndex)) {

		switch (prop)
		{
		case EAffectedProperty::Base:
			Stats[statIndex].AddValue(value);
			break;
		case EAffectedProperty::Min:
			Stats[statIndex].AddMin(value);
			break;
		case EAffectedProperty::Max:
			Stats[statIndex].AddMax(value);
			break;
		case EAffectedProperty::Buff:
			Stats[statIndex].AddBuff(value);
			break;
		case EAffectedProperty::None:
			break;
		default:
			break;
		}

		// update the display widget
		UpdateStatWidget(Stats[statIndex].StatName);
	}
}

void AURpg_Character::UpdateStatWidget(EStatName stat) {
	if (GetController() != nullptr) {
		AURpg_PlayerController* controlRef = Cast<AURpg_PlayerController>(GetController());
		if (controlRef != nullptr && controlRef->GetHUDInstance() != nullptr) {
			// update the HUD
			controlRef->GetHUDInstance()->UpdateStat(stat);
		}
	}
}