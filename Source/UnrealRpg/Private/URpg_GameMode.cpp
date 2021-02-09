// Copyright Jordan Duncan 2015 \\ Description=RPG Template
#include "URpg_GameMode.h"
#include "URpg_BpAsset_Paths.h"
// includes for our custom classes
#include "URpg_PlayerCharacter.h"
#include "URpg_HUD.h"

// * INITIALIZATION * //
// Constructor
AURpg_GameMode::AURpg_GameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {

	// default spawn style
	eSpawnStyle = ESpawnStyles::None;
	spawnIndex = 0;
	SpawnTag = "";

	// Set the default player pawn
	// Blueprinted Version, relies on the asset path obtained from the editor
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(*FURpg_BpAsset_Paths::DefaultPlayerCharacterBP);
	if (PlayerPawnBPClass.Class != nullptr)
	{
		// assign blueprint version
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	else {
		// Failsafe assigns native cpp version
		DefaultPawnClass = AURpg_PlayerCharacter::StaticClass();
	}
	// Set the default player controller
	// Blueprinted Version, relies on the asset path obtained from the editor
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBpClass(*FURpg_BpAsset_Paths::DefaultPlayerControllerBp);
	if (PlayerControllerBpClass.Class != nullptr) {
		// assign blueprint version
		PlayerControllerClass = PlayerControllerBpClass.Class;
	}
	else {
		// Failsafe assigns native cpp version
		PlayerControllerClass = AURpg_PlayerController::StaticClass();
	}
	// TODO: Assign Blueprint version of HUD in the Gamemode, only cpp assignment currently exists
	// Failsafe assigns native cpp version
	HUDClass = AURpg_HUD::StaticClass();
}

void AURpg_GameMode::BeginPlay() {

	if (!bHasSetSpawnStyle) {
		// set the spawn style
		SetESpawnStyle(eSpawnStyle);
	}

	Super::BeginPlay();

}
// * PLAYERLOGIN * //
class AActor* AURpg_GameMode::ChoosePlayerStart_Implementation(AController* Player) {
	if (!bHasSetSpawnStyle) {
		// set the spawn style
		SetESpawnStyle(eSpawnStyle);
	}

	// refrence to hold our actor
	AActor* aRef = nullptr;

	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, "Start Choose Start");
	// get player start based on spawn style
	switch (eSpawnStyle)
	{
	case ESpawnStyles::Sequence:
		aRef = GetPlayerStart_Sequence();
		break;
	case ESpawnStyles::Random:
		aRef = GetPlayerStart_Random();
		break;
	case ESpawnStyles::RandomSequence:
		aRef = GetPlayerStart_RandomSequence();
		break;
	case ESpawnStyles::ByTag:
		aRef = GetPlayerStart_ByTag(SpawnTag);
		break;
	case ESpawnStyles::None:
		if (DefaultPlayerStart != nullptr) {
			aRef = DefaultPlayerStart;
		}
		else if (playerStarts.IsValidIndex(0)) {
			aRef = playerStarts[0];
		}
		break;
	default:
#if !UE_BUILD_SHIPPING
		//UE_LOG(GeneralLog, Warning, TEXT("Invalid Spawn Style selected: Using default"));
#endif // !UE_BUILD_SHIPPING
		//aRef = FindPlayerStart(Player);
		if (DefaultPlayerStart != nullptr) {
			aRef = DefaultPlayerStart;
		}
		else if (playerStarts.IsValidIndex(0)) {
			aRef = playerStarts[0];
		}
		break;
	}
	// check if we have a actor
	if (aRef == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, "Unable to find suitable player start!");
#if !UE_BUILD_SHIPPING
		//UE_LOG(DebugLog, Warning, TEXT("Unable to find suitable player start! Using backup methods"));
#endif // !UE_BUILD_SHIPPING
		if (DefaultPlayerStart != nullptr) {
			aRef = DefaultPlayerStart;
		}
		else if (playerStarts.IsValidIndex(0)) {
			aRef = playerStarts[0];
		}
		// if we still don't have an actor return nullptr
		if (aRef == nullptr) {
#if !UE_BUILD_SHIPPING
			//UE_LOG(DebugLog, Error, TEXT("FAILED to find suitable player start!"));
#endif // !UE_BUILD_SHIPPING
			return nullptr;
		}
	}
	// if we found an actor return it
	return aRef;
}



/** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerAController. */
void AURpg_GameMode::PostLogin(APlayerController* NewPlayer) {
	Super::PostLogin(NewPlayer);
	
	// get the controller as our custom player controller
	AURpg_PlayerController* controlRef = Cast<AURpg_PlayerController>(NewPlayer);
	
	//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Cyan, "Detect Post Login");
	if (controlRef != nullptr) {
		//	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Cyan, "Run Post Login");
			// tell the controller to initialize Post login Events
		controlRef->CLIENT_RunPostLogin();

	}
	
}

// * PLAYER START POINT LOGIC * //
class AActor* AURpg_GameMode::GetPlayerStart_Sequence() {
	AActor* aRef = nullptr;
	// check the spawn index is valid
	spawnIndex = spawnIndex >= playerStarts.Num() ? 0 : spawnIndex;

	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, "Sequence at index " + FString::SanitizeFloat(spawnIndex));

	if (playerStarts.IsValidIndex(spawnIndex)) {
		// get the player start from the index
		aRef = playerStarts[spawnIndex];
	}
	// increment the spawn index
	++spawnIndex;


	return aRef;
}
class AActor* AURpg_GameMode::GetPlayerStart_Random() const {
	AActor* aRef = nullptr;
	// get a random index
	int32 i = FMath::RandRange(0, playerStarts.Num() - 1);
	// check the index is valid
	if (playerStarts.IsValidIndex(i)) {
		// get the player start from the index
		aRef = playerStarts[i];
	}

	return aRef;
}
class AActor* AURpg_GameMode::GetPlayerStart_RandomSequence() {
	AActor* aRef = nullptr;
	// currently same behavior as sequence only the array has been shuffled
	aRef = GetPlayerStart_Sequence();
	return aRef;
}
// search for a player start by tag
// only returns the first matching tag found Unique tags are recomended
class AActor* AURpg_GameMode::GetPlayerStart_ByTag(FName tag) const {
	AActor* aRef = nullptr;

	// iterate through player starts
	for (int32 i = 0; i < playerStarts.Num(); ++i) {
		// check if the player start has the searched tag
		if (playerStarts.IsValidIndex(i) && playerStarts[i]->PlayerStartTag == tag) {
			// if the searched tag is found assign it to the refrence
			aRef = playerStarts[i];
			// a valid start has been found so we can break out of the loop
			break;
		}
	}

	return aRef;
}

void AURpg_GameMode::ShufflePlayerStarts() {
	// can't shuffle if their is not more then one element so return in that case
	if (playerStarts.Num() <= 1) {
		return;
	}

	TArray<APlayerStart*> aRefs;
	aRefs.SetNum(playerStarts.Num());

	for (int32 i = 0; i < playerStarts.Num(); ++i) {
		
		// get a random index in the array
		int32 newIndex = FMath::RandRange(0, playerStarts.Num() - 1);
		// if we got our old index bump the number a unit
		if (newIndex == i) {
			// if the index is zero jump up to the max else bump the number down
			newIndex = newIndex <= 0 ? playerStarts.Num() - 1 : --newIndex;
		}
		

		GEngine->AddOnScreenDebugMessage(-1, 500, FColor::Blue, "Shuffling: " + FString::SanitizeFloat(i) + " newIndex = " + FString::SanitizeFloat(newIndex));
		// if a new actor is already assigned
		if (aRefs[newIndex] != nullptr) {

			bool bFoundIndex = false;
			int32 newIndex2 = newIndex;
			GEngine->AddOnScreenDebugMessage(-1, 500, FColor::Red, " newIndex taken ");
			// loop through the array looking for aan empty spot that is not our old one
			for (int32 j = 0; j < playerStarts.Num(); ++j) {
				// check if the index is our old one or taken
				if (newIndex2 == i || aRefs[newIndex2] != nullptr) {
					// if the index is zero jump up to the max else bump the number down
					newIndex2 = newIndex2 <= 0 ? playerStarts.Num() - 1 : --newIndex2;
				}
				else {
					bFoundIndex = true;
					newIndex = newIndex2;
					break;
				}
			}
			if (bFoundIndex) {
				// insert the current actor into its new spot
				aRefs[newIndex] = playerStarts[i];
			}
			else {
				// if the only open slot is our old one perform a swap
				APlayerStart* aRef = aRefs[newIndex];
				aRefs[newIndex] = playerStarts[i];
				aRefs[i] = aRef;
			}
		}
		else {
			// insert the current actor into its new spot
			aRefs[newIndex] = playerStarts[i];
		}
		
		
		
	}

	for (int32 i = 0; i < aRefs.Num(); ++i) {
		if (aRefs[i] != nullptr) {
			GEngine->AddOnScreenDebugMessage(-1, 500, FColor::Green, "Index " + FString::SanitizeFloat(i) + " Name: " + aRefs[i]->GetName());
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 500, FColor::Green, "Index " + FString::SanitizeFloat(i) + " NULL ");
		}
	}

	playerStarts = aRefs;
}

TArray<APlayerStart*> AURpg_GameMode::GetAllPlayerStarts() {
	// clear the player starts array
	playerStarts.Empty();
	// make sure we can get the world
	if (GetWorld() != nullptr) {
		// find all player starts
		for (TActorIterator<APlayerStart> ActorItr(GetWorld()); ActorItr; ++ActorItr)
		{
			// add the player starts to the playerStarts array
			playerStarts.Add(*ActorItr);
			//GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Blue, "Adding " + ActorItr->GetName());
		}
	}
	// return the array
	return playerStarts;
}

// * PLAYER SPAWNING / KILLING * //
// Kill Input player pawn
void AURpg_GameMode::KillPlayer_Implementation(AURpg_PlayerController* InPlayer, bool bOverrideIsImmortal) {
	if ((HasAuthority() && InPlayer != nullptr && InPlayer->GetIsAlive() == true) && (bOverrideIsImmortal == true || InPlayer->GetIsImmortal() == false)) {
		if (InPlayer->GetPawn() != nullptr && GetWorld() != nullptr) {
			AURpg_Character* pawn = Cast<AURpg_Character>(InPlayer->GetPawn());
			if (pawn != nullptr) {

				pawn->OnDeath();

				InPlayer->OnPlayerDeath();
				InPlayer->UnPossess();

				GetWorld()->DestroyActor(pawn);
				
				InPlayer->SetCanSpawn(true);
				InPlayer->SetLockoutDeathNSpawning(false);

			}
			else {
				//UE_LOG(DebugLog, Error, TEXT("KILLPLAYER Target not a URpg_Character"));
			}
			
		}
	}
}
/*
bool AURpg_GameMode::KillPlayer_Validate(AURpg_PlayerController* InPlayer) {
	return true;
}
*/

// Respawn player
void AURpg_GameMode::RespawnPlayer_Implementation(AURpg_PlayerController* InPlayer) {
	GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "Init Spawn");
	if (HasAuthority() && InPlayer != nullptr && InPlayer->GetIsAlive() == false && InPlayer->GetCanSpawn() == true && GetWorld() != nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "Spawn Valid");
		// transform for spawn location and rotation
		FTransform spawnTransform = FindPlayerStart(InPlayer)->GetTransform();
		spawnTransform.SetScale3D(FVector(1, 1, 1));
		// spawn params
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = InPlayer;
		spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		// ref to hold our character
		AURpg_PlayerCharacter* newCharRef = nullptr;
		//check that the assigned character class is valid
		if (InPlayer->GetCharacterClass()->IsChildOf(AURpg_PlayerCharacter::StaticClass())) {
			GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "Spawn class valid");
			newCharRef = GetWorld()->SpawnActor<AURpg_PlayerCharacter>(InPlayer->GetCharacterClass(), spawnTransform, spawnParams);
		}
		else if (DefaultPawnClass->IsChildOf(AURpg_PlayerCharacter::StaticClass())){
			GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "Default class valid");
			newCharRef = GetWorld()->SpawnActor<AURpg_PlayerCharacter>(DefaultPawnClass, spawnTransform, spawnParams);
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 50, FColor::Red, "no valid class");
		}
		if (newCharRef != nullptr) {
			InPlayer->Possess(newCharRef);

			InPlayer->RunRespawnEvents();

			InPlayer->SetIsAlive(true);
			InPlayer->SetCanSpawn(false);
			InPlayer->SetLockoutDeathNSpawning(false);
		}
	}
}
/*
bool AURpg_GameMode::RespawnPlayer_Validate(AURpg_PlayerController* InPlayer) {
	return true;
}
*/

void AURpg_GameMode::KillCharacter_Implementation(AURpg_Character* InCharacter, bool bOverrideIsImmortal) {

}