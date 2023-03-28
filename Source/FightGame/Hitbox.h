// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Hitbox.generated.h"


UCLASS()
class FIGHTGAME_API AHitbox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHitbox();

	UFUNCTION(BlueprintCallable)
	void setActive(FVector PlayerPosition, FTransform CurrentHitboxTransform);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Parent")
	AActor* OwnerReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	bool isActive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	FVector HitboxLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float HitboxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	FVector AttackForce;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* StrikeMaterial;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* DefaultMaterial;
	UPROPERTY(EditAnywhere, Category = "Materials")
	UMaterialInterface* HurtboxMaterial;

	FTransform InitialTransform;

	bool getIsActive() { return isActive; }
	float getDamage() { return HitboxDamage; }
	FVector* getAttackForce() { return &AttackForce; }
	void setDamage(float Damage) { HitboxDamage = Damage; }
	void setAttackForce(FVector* _AttackForce) { AttackForce = *_AttackForce; }

	UFUNCTION(BlueprintCallable)
	void Reset();

	void setInitialHurtboxMaterial() { Mesh->SetMaterial(0, HurtboxMaterial); };
	
	void SetNewLocation() { Mesh->SetWorldLocation({ 0.0f, 0.0f, 0.0f }); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UStaticMeshComponent* getMesh() { return Mesh; }
};
