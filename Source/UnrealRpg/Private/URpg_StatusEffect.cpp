// Fill out your copyright notice in the Description page of Project Settings.
#include "URpg_StatusEffect.h"



// * CONSTRUCTOR * //
UURpg_StatusEffect::UURpg_StatusEffect(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	Name = "";
}
// * TICK * //
void UURpg_StatusEffect::Tick(float DeltaTime) {
#if !UE_BUILD_SHIPPING
	//UE_LOG(DebugLog, Warning, TEXT("Status Effect is ticking continuously"));
#endif // !UE_BUILD_SHIPPING
	if (bIsActive) {
		RunEffect(DeltaTime);
	}
}
// the effect will only tick if the rate is set to zero for continuous
bool UURpg_StatusEffect::IsTickable() const {
	bool bTickIt = false;
	if (Target != nullptr && Target->GetWorld() != nullptr) {
		float tickRate = Params.GetTickRate();
		bTickIt = Target->GetWorld()->HasBegunPlay() && (tickRate <= 0 ? true : false);
	}
	return bTickIt;
}
TStatId UURpg_StatusEffect::GetStatId() const { return Super::GetStatID(); }

// * EFFECT CONTROL * //
void UURpg_StatusEffect::RunEffect(float DeltaTime) {
#if !UE_BUILD_SHIPPING
	//UE_LOG(DebugLog, Warning, TEXT("Status Effect is ticking"));
#endif // !UE_BUILD_SHIPPING
	// Check we still have valid taget
	if (Target != nullptr && !Target->IsPendingKillOrUnreachable()) {
		// increment ticks
		Ticks += DeltaTime;
#if !UE_BUILD_SHIPPING
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(39, 100, FColor::Red, "Ticks: " + FString::SanitizeFloat(Ticks));
		}
#endif // !UE_BUILD_SHIPPING
		switch (Params.PowerUpEffectStyle)
		{
		
		case EPowerUpEffectStyle::NextAttack:
		case EPowerUpEffectStyle::NextDamaged:
		case EPowerUpEffectStyle::NextDeath:
		case EPowerUpEffectStyle::NextHit:
		case EPowerUpEffectStyle::NextSuccessfulAttack:

			Remove();
			break;
		case EPowerUpEffectStyle::Permanent:
			Remove();
			break;
		case EPowerUpEffectStyle::TimedBuff:
		{
			float val = Params.Duration <= 0 ? Params.Value : Params.Value * DeltaTime / Params.Duration;

			for (int32 i = 0; i < Params.SNames.Num(); ++i) {
#if !UE_BUILD_SHIPPING
				if (GEngine) {
					GEngine->AddOnScreenDebugMessage(40, 100, FColor::Red, "Val: " + FString::SanitizeFloat(val));
				}
#endif // !UE_BUILD_SHIPPING
				if(Params.SNames[i] == EStatName::Health && Params.AffectedProperty == EAffectedProperty::Base){
					FDamageEvent DamageEvent;
					Target->TakeDamage(-val, DamageEvent, nullptr, nullptr);
				}
				else {
					Target->AddStatValue_ByName(Params.SNames[i], val, Params.AffectedProperty);
				}
			}
			for (int32 i = 0; i < Params.ANames.Num(); ++i) {
				//	Owner->AddAttributeValue_ByName(Params.ANames[i], Params.Value, Params.AffectedProperty);
			}
			// if our total time spent is greater then or equal to duration stop the effect
			if (Ticks >= Params.Duration) {
				Remove();
			}
			break;
		}
		default:
			Remove();
			break;
		}

	} else  {
		Remove();
	}

}

void UURpg_StatusEffect::Activate(AURpg_Character* TargetActor) {
	if (bIsActive == false && TargetActor != nullptr && TargetActor->GetGameInstance() != nullptr) {
		if (WidgetStyle.GetDefaultObject() != nullptr) {
			// create the widget corresponding to this status effect
			WidgetInstance = CreateWidget<UURpg_StatusEffect_UserWidget>(TargetActor->GetGameInstance(), WidgetStyle);
		}
		// Set the Owner
		Target = TargetActor;
		// Get the World from the owner
		if (Target != nullptr) {
			UWorld* World = Target->GetWorld();
			if (World != nullptr) {
				Target->AddStatEffect(this);
				// make sure current ticks is set to 0
				Ticks = 0;
				// set is active to true
				bIsActive = true;
				// Check tick rate
				if (Params.GetTickRate() > 0) {
					EffectDelegate.BindUFunction(this, "RunEffect", Params.Duration / Params.GetTickRate());
					// Set the effect timer based on TickRate
					World->GetTimerManager().SetTimer(EffectTimer, EffectDelegate, Params.Duration / Params.GetTickRate(), true);
				}
			}
		}
	}
	
	
}

void UURpg_StatusEffect::Pause() {
	// Get the World from the owner
	if (Target != nullptr) {
		UWorld* World = Target->GetWorld();
		if (World != nullptr) {
			if (World->GetTimerManager().IsTimerPaused(EffectTimer)) {
				World->GetTimerManager().UnPauseTimer(EffectTimer);
			}
			else {
				World->GetTimerManager().PauseTimer(EffectTimer);
			}
		}
	}
}

void UURpg_StatusEffect::Reset() {
	// Get the World from the owner
	if (Target != nullptr) {
		UWorld* World = Target->GetWorld();
		if (World != nullptr) {
		}
	}
}

void UURpg_StatusEffect::Remove() {
	// Get the World from the owner
	if (Target != nullptr) {
		Target->RemoveStatEffect(this);
		UWorld* World = Target->GetWorld();
		if (World != nullptr) {
			World->GetTimerManager().ClearAllTimersForObject(this);
			GEngine->AddOnScreenDebugMessage(11, 100, FColor::Red, "CLEARTIMER");
		}
	}
	// mark the effect for garbage collection
	MarkPendingKill();
}