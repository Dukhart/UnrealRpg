// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#ifndef __UNREALRPG_H__
#define __UNREALRPG_H__

#include "Engine.h"

// custom global asset path strings
#include "URpg_BpAsset_Paths.h"
#include "URpg_TextureAsset_Paths.h"
#include "URpg_MeshAsset_Paths.h"

// usefull global statics
#include "Dons_StaticFunctionLibrary.h"

// Custom  global game logic
#include "URpg_GameInstance.h"
#include "URpg_GameMode.h"

// LOGS
//General Log
DECLARE_LOG_CATEGORY_EXTERN(GeneralLog, Log, All);
//General debug Log
DECLARE_LOG_CATEGORY_EXTERN(DebugLog, Log, All);
//Logging during game startup
DECLARE_LOG_CATEGORY_EXTERN(InitLog, Log, All);
//Logging for your AI system
DECLARE_LOG_CATEGORY_EXTERN(AILog, Log, All);
//Logging for Critical Errors that must always be addressed
DECLARE_LOG_CATEGORY_EXTERN(CriticalErrorsLog, Log, All);

#endif
