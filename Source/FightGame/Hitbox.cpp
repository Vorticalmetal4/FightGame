// Fill out your copyright notice in the Description page of Project Settings.


#include "Hitbox.h"


// Sets default values
AHitbox::AHitbox() :
	HitboxDamage(0.05f)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OwnerReference = GetOwner();

	InitialTransform.SetLocation(FVector(0.0f, 0.0f, 0.0f));
	InitialTransform.SetRotation(FQuat(0.0f, 0.0f, 0.0f, 0.0f));

}

// Called when the game starts or when spawned
void AHitbox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHitbox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHitbox::setActive(FVector PlayerPosition, FTransform CurrentHitboxTransform)
{

	CurrentHitboxTransform.SetLocation(PlayerPosition + CurrentHitboxTransform.GetLocation());
	Mesh->SetWorldTransform(CurrentHitboxTransform);
	Mesh->SetMaterial(0, StrikeMaterial);
	isActive = true;

}

void AHitbox::Reset()
{
	Mesh->SetWorldTransform(InitialTransform);
	Mesh->SetMaterial(0, DefaultMaterial);
	isActive = false;
}


