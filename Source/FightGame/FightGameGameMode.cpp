// Copyright Epic Games, Inc. All Rights Reserved.

#include "FightGameGameMode.h"
#include "FightGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFightGameGameMode::AFightGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
