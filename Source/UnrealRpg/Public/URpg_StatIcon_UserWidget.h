// Copyright Jordan Duncan 2015

#pragma once

#include "URpg_StatDisplay_UserWidget.h"

// include for stat data
#include "URpg_Stat_Struct.h"

#include "URpg_StatIcon_UserWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALRPG_API UURpg_StatIcon_UserWidget : public UURpg_StatDisplay_UserWidget
{
	GENERATED_BODY()
//private:
	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Stat, meta = (AllowPrivateAccess = true))
	//	EStatName StatName;
public:
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Update")
		//void SetPercent(float InPercent);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Colours")
		void SetColour(FColor InColor, int32 Index);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Colours")
		void AddColour(FColor InColor, int32 Index);
	
	
};
