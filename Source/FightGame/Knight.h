// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FightGameCharacter.h"
#include "Knight.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTGAME_API AKnight : public AFightGameCharacter
{
	GENERATED_BODY()

public:
	AKnight();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particles")
	UParticleSystem* ShieldDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particles")
	float ZParticlesLocationAux;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particles")
	float YParticlesLocationAux;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particles")
	float YParticlesLocationAuxCrouched;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Particles")
	FVector ParticlesLocationAux;

	UFUNCTION(BlueprintCallable)
	void SetParticlesLocationAux();

};
