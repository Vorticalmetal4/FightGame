// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameInstance.generated.h"

UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	CharacKnight UMETA(DisplayName = "Knight"),
	CharacVampire UMETA(DisplayName = "Vampire"),
	CharacArcher  UMETA(DisplayName = "Archer")

};


UCLASS()
class FIGHTGAME_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()

public: 
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		ECharacterClass CharacterClass;
	
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Reference")
		ECharacterClass CharacterClass2;
};
