// Copyright Jordan Duncan 2015
#include "URpg_BasePowerUp.h"


// * INIT * //
// Sets default values
AURpg_BasePowerUp::AURpg_BasePowerUp(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Create the CollisionComponent
	CollisionComp = CreateDefaultSubobject<USphereComponent>("Collision");
	// Set the Collision Component to the Root
	RootComponent = CollisionComp;
	// Set default sphere size
	CollisionComp->SetSphereRadius(50.0f);
	// Set Collision params
	//CollisionComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionProfileName("Trigger");
	//CollisionComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	// Set Pyshics of the collision component
	CollisionComp->SetSimulatePhysics(false);

	// Create the MeshComponent
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	// Attach the mesh to the root
	MeshComp->SetupAttachment(RootComponent);
	//FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);
	//MeshComp->AttachToComponent(RootComponent, AttachmentTransformRules);
	// Disable Collision on the Mesh
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

 	// Set this actor to be able to tick
	PrimaryActorTick.bCanEverTick = true;
	// start with tick disabled
	PrimaryActorTick.SetTickFunctionEnable(false);
	BindHitEvents();

	// Add default Affected character types
	AffectedCharacterTypes.Empty();
	AffectedCharacterTypes.AddUnique(ECharacterType::Player);
	AffectedCharacterTypes.AddUnique(ECharacterType::AI);
	AffectedCharacterTypes.AddUnique(ECharacterType::NPC);
	AffectedCharacterTypes.AddUnique(ECharacterType::Monster);
	AffectedCharacterTypes.AddUnique(ECharacterType::Animal);
}

// Called when the game starts or when spawned
void AURpg_BasePowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// * TICK * //
// Called every frame
void AURpg_BasePowerUp::Tick( float DeltaTime )
{
	for (int32 i = 0; i < RecentActorData.Num(); ++i) {
		RecentActorData[i].duration += DeltaTime;
		if (RecentActorData[i].duration > CharacterActivationDelay) {
			RecentActorData.RemoveAt(i, 1,false);
		}
	}
	// resize Recent Actor data
	RecentActorData.Shrink();
	if (RecentActorData.Num() <= 0) {
		// we only need to tick if tracking actors
		PrimaryActorTick.SetTickFunctionEnable(false);
	}
	Super::Tick( DeltaTime );
}

// * INTERFACES * //
// IsPowerUp
void AURpg_BasePowerUp::ActivatePowerUp_Implementation(AURpg_Character* TargetActor) {
#if !UE_BUILD_SHIPPING
	//UE_LOG(DebugLog, Warning, TEXT("Status Effect Start ACTIVATE"));
#endif // !UE_BUILD_SHIPPING
	if (TargetActor != nullptr) {
		// apply each effect of the power up
		for (int32 i = 0; i < PowerUpEffects.Num(); ++i) {
			if (PowerUpEffects[i].GetDefaultObject() == nullptr)
			{
				return;
			}
			// Get a ref to the default object
			UURpg_StatusEffect* Effect = PowerUpEffects[i].GetDefaultObject();


			if (PowerUpEffects[i] != nullptr) {
				bool bIsValid = false;
				// ATTRIBUTE EFFECTS
				// check if the power up affects Attributes
				if (Effect->GetParams().ANames.Num() > 0) {
					for (int32 a = 0; a < Effect->GetParams().ANames.Num(); ++a) {
						// break out of the loop when is valid is set
						if (bIsValid) { break; }
						// Find the stats on the character with the same name
						for (int32 c = 0; c < TargetActor->GetAttributes().Num(); ++c) {
							if (Effect->GetParams().ANames[a] == TargetActor->GetAttributes()[c].AtriName) {
								// Theres a match so the power up is valid
								bIsValid = true;
								break;
							}
						}
					}
				}
				// STAT EFFECTS
				// check if the power up affects stats
				if (Effect->GetParams().SNames.Num() > 0) {
					// apply power up effects to each affected Stat
					for (int32 s = 0; s < Effect->GetParams().SNames.Num(); ++s) {
						// break out of the loop when is valid is set
						if (bIsValid) { break; }
						// Find the stats on the character with the same name
						for (int32 c = 0; c < TargetActor->GetStats().Num(); ++c) {
							if (Effect->GetParams().SNames[s] == TargetActor->GetStats()[c].StatName) {
								// Theres a match so the power up is valid
								bIsValid = true;
								break;
							}
						}

					}
				}
				// check if the power up was validated
				if (bIsValid) {
					// create a new instance of the effect
					//UURpg_StatusEffect* NewEffect = NewObject<UURpg_StatusEffect>(TargetActor, PowerUpEffects[i].GetDefaultObject()->GetClass(), *PowerUpEffects[i].GetDefaultObject()->GetName());
					UURpg_StatusEffect* NewEffect = NewObject<UURpg_StatusEffect>(TargetActor, PowerUpEffects[i].GetDefaultObject()->GetClass());
#if !UE_BUILD_SHIPPING
					//UE_LOG(DebugLog, Warning, TEXT("Status Effect ACTIVATE"));
#endif // !UE_BUILD_SHIPPING
					
					// Activate the Effect
					NewEffect->Activate(TargetActor);
				}
			}
			
		}
	}
}

// * EVENTS * //
// * Binds Hit Events to power up activation
void AURpg_BasePowerUp::BindHitEvents() {
	if (CollisionComp != nullptr) {
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AURpg_BasePowerUp::OnOverlapBegin);
	}
}
// Checks if actor is valid to use the powerup before activating
void AURpg_BasePowerUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	bool bAbort = false;
	// Check that the overllaping actor is a character
	if (OtherActor != nullptr && OtherActor->GetClass()->IsChildOf (AURpg_Character::StaticClass())) {
		
		// Check Actor timer
		for (int32 i = 0; i < RecentActorData.Num(); i++)
		{
			if (RecentActorData[i].actor == OtherActor) {
				bAbort = true;
				break;
			}
		}

		// cast to a character
		AURpg_Character* CharacterRef = Cast<AURpg_Character>(OtherActor);
		if (CharacterRef != nullptr && !bAbort) {
			// Validate the character can use this power up
			for (int32 i = 0; i < AffectedCharacterTypes.Num(); ++i) {
				if (AffectedCharacterTypes[i] == CharacterRef->GetCharcterType()) {
					// Activate the power up
					RecentActorData.Add(FURpg_RecentActorData(OtherActor));
					// enable tick as we now have an actor to track
					if (PrimaryActorTick.IsTickFunctionEnabled() != true) {
						PrimaryActorTick.SetTickFunctionEnable(true);
					}
					Execute_ActivatePowerUp(this, CharacterRef);
					// break out of the loop we only want to activate the power up once
					break;

				}
			}
		}
	}
}

