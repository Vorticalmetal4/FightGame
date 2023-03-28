// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FightGameCharacter.h"
#include "Projectile.h"
#include "Archer.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTGAME_API AArcher : public AFightGameCharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	AProjectile* Arrow;

	UStaticMeshComponent* ArrowsMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Weapon")
	FTransform ArrowTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector ArrowsHitboxScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector AuxArrowPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float AuxArrowsHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float ArrowsVelocity;

public:
	AArcher();

};
