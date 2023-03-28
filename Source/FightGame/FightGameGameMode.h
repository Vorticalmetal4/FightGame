// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FightGameCharacter.h"
#include "FightGameGameMode.generated.h"


UCLASS(minimalapi)
class AFightGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFightGameGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	AFightGameCharacter* Player1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
    AFightGameCharacter* Player2;
};



