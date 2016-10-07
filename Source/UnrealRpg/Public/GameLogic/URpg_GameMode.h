// Copyright Jordan Duncan 2015 \\ Description=RPG Template
#pragma once

#include "GameFramework/GameMode.h"

#include "Dons_StaticFunctionLibrary.h"

#include "URpg_PlayerController.h"

#include "URpg_GameMode.generated.h"

UENUM(BlueprintType)
enum class ESpawnStyles : uint8 {
	Sequence,
	Random,
	RandomSequence,
	ByTag,


	None
};

UCLASS(minimalapi)
class AURpg_GameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	// * INITIALIZATION * //
	// Constructor
	AURpg_GameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	// called after the constructor
	virtual void BeginPlay() override;
	// * PLAYERLOGIN * //

	/**
	* Accept or reject a player attempting to join the server.  Fails login if you set the ErrorMessage to a non-empty string.
	* PreLogin is called before Login.  Significant game time may pass before Login is called, especially if content is downloaded.
	*
	* @param	Options					The URL options (e.g. name/spectator) the player has passed
	* @param	Address					The network address of the player
	* @param	UniqueId				The unique id the player has passed to the server
	* @param	ErrorMessage			When set to a non-empty value, the player will be rejected using the error message set
	*/
	//virtual void PreLogin(const FString& Options, const FString& Address, const TSharedPtr<const FUniqueNetId>& UniqueId, FString& ErrorMessage) override;

	/**
	* Called to login new players by creating a player controller, overridable by the game
	*
	* Sets up basic properties of the player (name, unique id, registers with backend, etc) and should not be used to do
	* more complicated game logic.  The player controller is not fully initialized within this function as far as networking is concerned.
	* Save "game logic" for PostLogin which is called shortly afterward.
	*
	* @param NewPlayer pointer to the UPlayer object that represents this player (either local or remote)
	* @param RemoteRole the remote role this controller has
	* @param Portal desired portal location specified by the client
	* @param Options game options passed in by the client at login
	* @param UniqueId platform specific unique identifier for the logging in player
	* @param ErrorMessage [out] error message, if any, why this login will be failing
	*
	* If login is successful, returns a new PlayerController to associate with this player. Login fails if ErrorMessage string is set.
	*
	* @return a new player controller for the logged in player, NULL if login failed for any reason
	*/
	//virtual APlayerController* Login(class UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const TSharedPtr<const FUniqueNetId>& UniqueId, FString& ErrorMessage) override;

	/** Called after a successful login.  This is the first place it is safe to call replicated functions on the PlayerAController. */
	virtual void PostLogin(APlayerController* NewPlayer) override;
	// determines what player start to use when spawning a character
	virtual class AActor* ChoosePlayerStart_Implementation(AController* Player) override;
public:
	// * PLAYER START POINT LOGIC * //
	UFUNCTION(BlueprintCallable, Category = Spawn)
		virtual class AActor* GetPlayerStart_Sequence();
	UFUNCTION(BlueprintCallable, Category = Spawn)
		virtual class AActor* GetPlayerStart_Random() const;
	UFUNCTION(BlueprintCallable, Category = Spawn)
		virtual class AActor* GetPlayerStart_RandomSequence();
	// search for a player start by tag
	// only returns the first matching tag found Unique tags are recomended
	UFUNCTION(BlueprintCallable, Category = Spawn)
		virtual class AActor* GetPlayerStart_ByTag(FName tag) const;
	// used by random sequence mode to reorder the player starts
	UFUNCTION(BlueprintCallable, Category = Spawn)
		virtual void ShufflePlayerStarts();
	UFUNCTION(BlueprintCallable, Category = Spawn)
		virtual TArray<APlayerStart*> GetAllPlayerStarts();

	// * PLAYER SPAWNING / KILLING * //
	// Kill Input player pawn
	//UFUNCTION(reliable, server, WithValidation, BlueprintNativeEvent, BlueprintCallable, Category = Spawn)
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Spawn)
	void KillPlayer(AURpg_PlayerController* InPlayer, bool bOverrideIsImmortal = false);
	void KillPlayer_Implementation(AURpg_PlayerController* InPlayer, bool bOverrideIsImmortal = false);
	
//	bool KillPlayer_Validate(AURpg_PlayerController* InPlayer);
	// Respawn player
	//UFUNCTION(reliable, server, WithValidation, BlueprintNativeEvent, BlueprintCallable, Category = Spawn)
	
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = Spawn)
		void RespawnPlayer(AURpg_PlayerController* InPlayer);
	void RespawnPlayer_Implementation(AURpg_PlayerController* InPlayer);
	
//	bool RespawnPlayer_Validate(AURpg_PlayerController* InPlayer);

protected:
	UPROPERTY()
		bool bHasSetSpawnStyle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
		APlayerStart* DefaultPlayerStart;
	// the tag to look for when spawning a player by Spawn Point Tag
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawn)
		FName SpawnTag;
	// the current index when spawning by sequence
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Spawn)
		int32 spawnIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Spawn)
		TArray<APlayerStart*> playerStarts;
	// Holds the spawning style to use when determining where to spawn a player
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		ESpawnStyles eSpawnStyle;
public:
	// * GETTERS AND SETTERS * //
	// Get Spawn Style
	UFUNCTION(BlueprintCallable, Category = Spawn)
		ESpawnStyles GetESpawnStyle() { return eSpawnStyle; }
	// Set Spawn Style
	UFUNCTION(BlueprintCallable, Category = Spawn)
		void SetESpawnStyle(ESpawnStyles newStyle) {
		eSpawnStyle = newStyle;
		GetAllPlayerStarts();

		TArray<AActor*> aRefs;

		switch (eSpawnStyle)
		{
		case ESpawnStyles::Sequence:
			aRefs.Empty();
			// cast the player starts to actors
			for (int32 i = 0; i < playerStarts.Num(); ++i) {
				aRefs.Add(Cast<AActor>(playerStarts[i]));
			}
			// sort the player starts
			aRefs = UDons_StaticFunctionLibrary::SortActorsAlphabetically(aRefs);
			// clear the player starts
			playerStarts.Empty();
			for (int32 i = 0; i < aRefs.Num(); ++i) {
				// put the sorted player starts back
				playerStarts.Add(Cast<APlayerStart>(aRefs[i]));
			}
			break;
		case ESpawnStyles::RandomSequence:
			ShufflePlayerStarts();
		default:
			break;
		}
		bHasSetSpawnStyle = true;
	}
};




