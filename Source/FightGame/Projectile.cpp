// Fill out your copyright notice in the Description page of Project Settings.
#include "Projectile.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AProjectile::AProjectile()
	:isActive(false),
	Damage(0.1f),
	InitialZone(false)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isActive)
	{
		CheckCollision();
		if (!isFlipped)
		{
			CurrentLocation = {CurrentLocation.X, CurrentLocation.Y - DeltaTime * Velocity, CurrentLocation.Z };
			HitboxMesh->SetWorldLocation({CurrentLocation.X, CurrentLocation.Y - 5, CurrentLocation.Z});
		}
		else
		{
			CurrentLocation = { CurrentLocation.X, CurrentLocation.Y + DeltaTime * Velocity, CurrentLocation.Z };
			HitboxMesh->SetWorldLocation({ CurrentLocation.X, CurrentLocation.Y - 5, CurrentLocation.Z });
		}

		BodyMesh->SetWorldLocation(CurrentLocation);

		if (abs(CurrentLocation.Y - InitialPosition) > MaxDistance)
		{
			isActive = false;
			BodyMesh->SetWorldLocation({ 0.0f, -10000.0f, -10000.0f });
			MainHitbox->getMesh()->SetWorldLocation({ 0.0f, -10000.0f, -10000.0f });
		}
	}
	else if (!InitialZone)
	{
			BodyMesh->SetWorldLocation({ 0.0f, -1000.0f, -1000.0f });
			MainHitbox->getMesh()->SetWorldLocation({ 0.0f, -1000.0f, -1000.0f });
			InitialZone = true;
	}
}

void AProjectile::ShootStarted(FVector ShootLocation, float AuxHitbox, FVector AuxLocation, bool isOwnerFlipped)
{
	InitialPosition = ShootLocation.Y;
	CurrentLocation = { ShootLocation.X + 10, ShootLocation.Y - 27, ShootLocation.Z + 135 };
	isActive = true;
	InitialZone = false;

	if (isOwnerFlipped != isFlipped)
	{
		CurrentRotation = BodyMesh->GetRelativeTransform().GetRotation();
		BodyMesh->SetRelativeRotation({ CurrentRotation.W, CurrentRotation.X, CurrentRotation.Y + 180, CurrentRotation.Z });
		isFlipped = isOwnerFlipped;
	}

	if (!isFlipped)
		HitboxTransform.SetLocation({ShootLocation.X, ShootLocation.Y - AuxHitbox, ShootLocation.Z});
	else
		HitboxTransform.SetLocation({ ShootLocation.X, ShootLocation.Y + AuxHitbox, ShootLocation.Z });

	BodyMesh->SetWorldLocation(CurrentLocation);
	MainHitbox->setActive(CurrentLocation, HitboxTransform);
	CheckCollision();
}

void AProjectile::CheckCollision()
{
	if (OtherPlayer)
	{
		if (OtherPlayer->getCollisionCapsule())
		{
			if (OtherPlayer->getCollisionCapsule()->IsOverlappingActor(MainHitbox))
			{
				isActive = false;
				OtherPlayer->HitByProjectile(Damage);
			}
		}
	}
}