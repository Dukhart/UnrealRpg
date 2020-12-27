// Copyright Jordan Duncan 2015 \\ Description=RPG Template

#include "UnrealRpg.h"

//General Log
DEFINE_LOG_CATEGORY(GeneralLog);
//General debug Log
DEFINE_LOG_CATEGORY(DebugLog);
//Logging during game startup
DEFINE_LOG_CATEGORY(InitLog);
//Logging for the AI system
DEFINE_LOG_CATEGORY(AILog);
//Logging for Critical Errors that MUST be addressed
DEFINE_LOG_CATEGORY(CriticalErrorsLog);
//"This is a message to yourself during runtime!"
//UE_LOG(InitLog, Warning, TEXT("This is a message to yourself during runtime!"));

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, UnrealRpg, "UnrealRpg" );
 