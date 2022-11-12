// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "FightGameCharacter.h"
#include "FightCamera.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTGAME_API AFightCamera : public ACameraActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Location")
	float XLocation;

	float CameraZoom;

public:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	AFightGameCharacter* Player1Ref;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Players")
	AFightGameCharacter* Player2Ref;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraC;
};
