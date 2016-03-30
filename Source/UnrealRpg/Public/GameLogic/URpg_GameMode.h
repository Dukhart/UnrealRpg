// Copyright Jordan Duncan 2015 \\ Description=RPG Template
#pragma once

#include "GameFramework/GameMode.h"
#include "URpg_GameMode.generated.h"

UCLASS(minimalapi)
class AURpg_GameMode : public AGameMode
{
	GENERATED_BODY()

protected:
	// * INTITIALIZATION * //
	// Constructor
	AURpg_GameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

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

};




