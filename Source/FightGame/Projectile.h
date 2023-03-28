// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hitbox.h"
#include "FightGameCharacter.h"
#include "Projectile.generated.h"

UCLASS()
class FIGHTGAME_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isFlipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	AHitbox* MainHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FTransform HitboxTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* HitboxMesh;

	UFUNCTION(BlueprintCallable)
	void ShootStarted(FVector ShootLocation, float AuxHitbox, FVector AuxLocation, bool isOwnerFlipped);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enemy")
	AFightGameCharacter* OtherPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isActive;

	bool InitialZone;

	FVector CurrentLocation;
	FQuat CurrentRotation;

	float Damage;
	float InitialPosition;

	void CheckCollision();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
