// Copyright Jordan Duncan 2015

#pragma once

#include "Object.h"

#include "URpg_Stat_Struct.h"
#include "URpg_Attribute_Struct.h"

#include "URpg_IsPowerUp.generated.h"

/**
 * 
 */
UINTERFACE(Blueprintable)
class UNREALRPG_API UURpg_IsPowerUp : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IURpg_IsPowerUp {
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "UseItem")
	void ActivatePowerUp(AURpg_Character* TargetActor);
};