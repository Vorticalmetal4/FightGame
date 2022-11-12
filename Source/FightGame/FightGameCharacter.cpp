// Copyright Epic Games, Inc. All Rights Reserved.

// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "FightGameCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/MovementComponent.h"
#include <HAL/MallocBinned3.h>

AFightGameCharacter::AFightGameCharacter()
	:Health(1.00f),
	wasLightAttackUsed(false),
	wasMediumAttackUsed(false),
	wasHardAttackUsed(false),
	isWalking(false),
	isFlipped(false),
	wasAttackConected(false),
	isBlocking(false),
	isCrouching(false),
	CanMove(false),
	canPlayNewAnimation(true),
	canStartSpecialAnimation(false),
	hasSpecialAnimationFinished(false),
	MaxDistance(850.0f),
	WalkingSpeed(0.75f),
	LightAttackDamage(0.05f),
	LightCrouchingAttack(0.04),
	MediumAttackDamage(0.075f),
	HardAttackDamage(0.1f),
	XPosition(100.0f),
	Scale(FVector(0.0f, 0.0f, 0.0f)),
	Transform(FTransform()),
	OtherPlayer(nullptr),
	CharacterMovement(nullptr),
	Mesh(nullptr)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Face in the direction we are moving..
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->GravityScale = 2.f;
	GetCharacterMovement()->AirControl = 0.80f;
	GetCharacterMovement()->JumpZVelocity = 1000.f;
	GetCharacterMovement()->GroundFriction = 3.f;
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
	GetCharacterMovement()->MaxFlySpeed = 600.f;
	GetCharacterMovement()->bOrientRotationToMovement = false;


	CurrentPosition = EPosition::StandUp;
	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

}

//////////////////////////////////////////////////////////////////////////
// Input

void AFightGameCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFightGameCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFightGameCharacter::StopJumping);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFightGameCharacter::MoveRight);

	PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &AFightGameCharacter::LightAttack);
	PlayerInputComponent->BindAction("MediumAttack", IE_Pressed, this, &AFightGameCharacter::MediumAttack);
	PlayerInputComponent->BindAction("HardAttack", IE_Pressed, this, &AFightGameCharacter::HardAttack);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFightGameCharacter::StartCrouching);
	PlayerInputComponent->BindAxis("CrouchGamepad", this, &AFightGameCharacter::StartCrouchingGp);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFightGameCharacter::StopCrouching);

	PlayerInputComponent->BindAction("Block", IE_Pressed, this, &AFightGameCharacter::Block);
	PlayerInputComponent->BindAction("Block", IE_Released, this, &AFightGameCharacter::Block);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &AFightGameCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &AFightGameCharacter::TouchStopped);

}


void AFightGameCharacter::MoveRight(float Value)
{
	if (!isCrouching && !isBlocking && Health > 0 && CanMove)
	{
		if (Value < -0.30f)
		{
			if (!isFlipped)
			{
				if (MaxDistance >= abs(CharacterMovement->GetActorLocation().Y - OtherPlayerMovement->GetActorLocation().Y) + Value)
					AddMovementInput({0.0f, -1.0f, 0.0}, Value);
				WalkingValue = -WalkingSpeed;
			}
			else
			{
				AddMovementInput({0.0f, -1.0f, 0.0f}, Value);
				WalkingValue = WalkingSpeed;
			}
			if (MovementDirection != EMovementDirection::Jumping)
			{
				MovementDirection = EMovementDirection::Left;
				isWalking = true;
			}
		}
		else if (Value > 0.30f)
		{
			if (isFlipped)
			{
				if (MaxDistance >= abs(CharacterMovement->GetActorLocation().Y - OtherPlayerMovement->GetActorLocation().Y) - Value)
					AddMovementInput({0.0f, -1.0f, 0.0f}, Value);
				WalkingValue = -WalkingSpeed;
			}
			else
			{
				AddMovementInput({0.0f, -1.0f, 0.0f}, Value);
				WalkingValue = WalkingSpeed;
			}

			if (MovementDirection != EMovementDirection::Jumping)
			{
				MovementDirection = EMovementDirection::Right;
				isWalking = true;
			}
		}
		else
		{
			if (MovementDirection != EMovementDirection::Jumping)
			{
				MovementDirection = EMovementDirection::NotMoving;
				isWalking = false;
			}
		}
	}
}	

void AFightGameCharacter::Jump()
{
	if (MovementDirection != EMovementDirection::Jumping && !isBlocking && Health > 0 && CanMove)
	{
		isCrouching = false;
		MovementDirection = EMovementDirection::Jumping;
		ACharacter::Jump();
	}
}

void AFightGameCharacter::StopJumping()
{
	ACharacter::StopJumping();
	MovementDirection = EMovementDirection::NotMoving;
}

void AFightGameCharacter::StartCrouchingGp(float Value)
{
	if (Value <= -0.5)
	{
		StartCrouching();
		UsingGamepad = true;
	}
	else if (isCrouching && UsingGamepad)
		StopCrouching();
}

void AFightGameCharacter::StartCrouchingKeyB()
{
	UsingGamepad = false;
	StartCrouching();
}



void AFightGameCharacter::TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	// jump on any touch
	Jump();
	MovementDirection = EMovementDirection::Jumping;
}

void AFightGameCharacter::TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	StopJumping();
}

void AFightGameCharacter::LightAttack()
{
	if (!isAttacking && Health > 0 && CanMove)
	{
		wasLightAttackUsed = true;
		isAttacking = true;

		if (!isCrouching)
			Hitbox->setDamage(LightAttackDamage);
		else
			Hitbox->setDamage(LightCrouchingAttack);

		HitboxTransform = LightAttackHitbox;

		if (!isFlipped)
			HitboxTransform.SetLocation({ HitboxTransform.GetLocation().X, HitboxTransform.GetLocation().Y * -1, HitboxTransform.GetLocation().Z });
	}

}

void AFightGameCharacter::MediumAttack()
{
	if (!isAttacking && Health > 0 && CanMove)
	{
		wasMediumAttackUsed = true;
		isAttacking = true;
		Hitbox->setDamage(MediumAttackDamage);
		HitboxTransform = MediumAttackHitbox;
		if (!isFlipped)
			HitboxTransform.SetLocation({ HitboxTransform.GetLocation().X, HitboxTransform.GetLocation().Y * -1, HitboxTransform.GetLocation().Z });
	}
}

void AFightGameCharacter::HardAttack()
{
	if (!isAttacking && Health > 0 && CanMove)
	{
		wasHardAttackUsed = true;
		isAttacking = true;
		Hitbox->setDamage(HardAttackDamage);
		HitboxTransform = HardAttackHitbox;
		if (!isFlipped)
			HitboxTransform.SetLocation({ HitboxTransform.GetLocation().X, HitboxTransform.GetLocation().Y * -1, HitboxTransform.GetLocation().Z });
	}
}

void AFightGameCharacter::SetData(AFightGameCharacter* _OtherPLayer, bool _isPlayer1)
{
	OtherPlayer = _OtherPLayer;
	CharacterMovement = GetCharacterMovement();
	OtherPlayerMovement = OtherPlayer->GetCharacterMovement();
	if(GetCapsuleComponent())
		Mesh = GetCapsuleComponent() -> GetChildComponent(1);
	
	isPlayer1 = _isPlayer1;


	if (UpperPartHurtbox)
	{
		UpperPartMesh = UpperPartHurtbox->getMesh();
		UpperPartMesh->SetRelativeLocation(StandUpHurtboxTransform.GetLocation());
		UpperPartMesh->SetWorldScale3D(StandUpHurtboxTransform.GetScale3D());
		UpperPartHurtbox->setInitialHurtboxMaterial();
	}

	if(HeadHurtbox)
	{
		HeadMesh = HeadHurtbox->getMesh();
		HeadMesh->SetWorldScale3D(HeadHurtboxTransform.GetScale3D());
		HeadHurtbox->setInitialHurtboxMaterial();
		
		if (!isFlipped)
			HeadMesh->SetRelativeLocation(HeadHurtboxTransform.GetLocation());
		else
			HeadMesh->SetRelativeLocation(FlippedHeadHurtboxLocation);
	}

	if (Hitbox)
		Hitbox->Reset();

	if (isPlayer1)
		isFlipped = false;
	else
		ChangeDirection();

	CharacterMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::X);
}

void AFightGameCharacter::Block()
{
	isBlocking = !isBlocking;
	if (isBlocking && CanMove)
	{
		if (!isCrouching)
		{
			CurrentPosition = EPosition::Blocking;

			if (!isFlipped)
				HeadMesh->SetRelativeLocation(HeadBlockingHurtboxLocation);
			else
				HeadMesh->SetRelativeLocation(FlippedHeadBlockingHurtboxLocation);
		}
		else
		{
			CurrentPosition = EPosition::BlockingCrouched;

			if (!isFlipped)
				HeadMesh->SetRelativeLocation(HeadBlockingCrouchedHurtboxLocation);
			else
				HeadMesh->SetRelativeLocation(FlippedHeadBlockingCrouchedHurtboxLocation);
		}
	}
	else
	{
		if (!isCrouching)
		{
			CurrentPosition = EPosition::StandUp;

			if (!isFlipped)
				HeadMesh->SetRelativeLocation(HeadHurtboxTransform.GetLocation());
			else
				HeadMesh->SetRelativeLocation(FlippedHeadHurtboxLocation);
		}
		else
		{
			CurrentPosition = EPosition::Crouched;
			if (!isFlipped)
				HeadMesh->SetRelativeLocation(HeadCrouchingHurtboxLocation);
			else
				HeadMesh->SetRelativeLocation(FlippedHeadCrouchingHurtboxLocation);
		}
	}
	SetCollisionPosition();
}

void AFightGameCharacter::StartCrouching()
{
	if (CanMove)
	{
		isCrouching = true;

		if (!isBlocking)
		{
			CurrentPosition = EPosition::Crouched;
			if (!isFlipped)
				HeadMesh->SetRelativeLocation(HeadCrouchingHurtboxLocation);
			else
				HeadMesh->SetRelativeLocation(FlippedHeadCrouchingHurtboxLocation);
		}
		else
		{
			CurrentPosition = EPosition::BlockingCrouched;
			if (!isFlipped)
				HeadMesh->SetRelativeLocation(HeadBlockingCrouchedHurtboxLocation);
			else
				HeadMesh->SetRelativeLocation(FlippedHeadBlockingCrouchedHurtboxLocation);
		}
		SetCollisionPosition();
	}
}

void AFightGameCharacter::StopCrouching()
{
	if (!isAttacking && CanMove)
	{
		isCrouching = false;
		if (!isBlocking)
		{
			CurrentPosition = EPosition::StandUp;

			if (!isFlipped)
				HeadMesh->SetRelativeLocation(HeadHurtboxTransform.GetLocation());
			else
				HeadMesh->SetRelativeLocation(FlippedHeadHurtboxLocation);
		}
		else
		{
			CurrentPosition = EPosition::Blocking;

			if (!isFlipped)
				HeadMesh->SetRelativeLocation(HeadBlockingHurtboxLocation);
			else
				HeadMesh->SetRelativeLocation(FlippedHeadBlockingHurtboxLocation);
		}
		SetCollisionPosition();
	}
}

void AFightGameCharacter::SetCollisionPosition()
{
	switch (CurrentPosition)
	{
		case EPosition::StandUp:
			UpperPartMesh->SetWorldScale3D(StandUpHurtboxTransform.GetScale3D());
			UpperPartMesh->SetRelativeLocation(StandUpHurtboxTransform.GetLocation());
			CollisionCapsule->SetRelativeTransform(CapsuleTransform);
		break;

		case EPosition::Blocking:
			UpperPartMesh->SetWorldScale3D(BlockingHurtboxTransform.GetScale3D());
			UpperPartMesh->SetRelativeLocation(BlockingHurtboxTransform.GetLocation());
			CollisionCapsule->SetRelativeTransform(BlockingCapsuleTransform);
		break;

		case EPosition::Crouched:
			UpperPartHurtbox->getMesh()->SetRelativeLocation(CrouchingHurtboxTransform.GetLocation());
			UpperPartMesh->SetWorldScale3D(CrouchingHurtboxTransform.GetScale3D());
			CollisionCapsule->SetRelativeTransform(CrouchingCapsuleTransform);
		break;

		case EPosition::BlockingCrouched:
			UpperPartMesh->SetWorldScale3D(BlockingCrouchedHurtboxTransform.GetScale3D());
			UpperPartMesh->SetRelativeLocation(BlockingCrouchedHurtboxTransform.GetLocation());
			CollisionCapsule->SetRelativeScale3D(BlockingCrouchedCapsuleTransform.GetScale3D());
			if(isFlipped)
				CollisionCapsule->SetRelativeLocation({ BlockingCrouchedCapsuleTransform.GetLocation().X, BlockingCrouchedCapsuleTransform.GetLocation().Y + AuxBlockigCrouchedCapsuleTransform, BlockingCrouchedCapsuleTransform.GetLocation().Z});
			else
				CollisionCapsule->SetRelativeLocation({ BlockingCrouchedCapsuleTransform.GetLocation().X, BlockingCrouchedCapsuleTransform.GetLocation().Y - AuxBlockigCrouchedCapsuleTransform, BlockingCrouchedCapsuleTransform.GetLocation().Z});

		break;
	}
}

void AFightGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(OtherPlayer && Health > 0)
	{
		if(CharacterMovement)
		{
			if(OtherPlayerMovement)
			{
				
				if (CharacterMovement->GetActorLocation().Y >= OtherPlayerMovement->GetActorLocation().Y)
				{
					if (isFlipped)
						ChangeDirection();
				}
				else
				{
					if (!isFlipped)
						ChangeDirection();
				}

			}
		}
	}
}

void AFightGameCharacter::ChangeDirection()
{
	if (Mesh)
	{
		Transform = Mesh->GetRelativeTransform();
		Scale = Transform.GetScale3D();
		Transform.SetScale3D({Scale.X, Scale.Y * -1, Scale.Z});
		isFlipped = !isFlipped;
		Mesh->SetRelativeTransform(Transform);
		if (isFlipped)
			HeadMesh->SetRelativeLocation(FlippedHeadHurtboxLocation);
		else
			HeadMesh->SetRelativeLocation(HeadHurtboxTransform.GetLocation());
	}
}

void AFightGameCharacter::ApplyDamage(float Damage)
{
	if (isBlocking)
		Damage /= 2.0;

	Health -= Damage;
	OtherPlayer->wasAttackConected = true;
	wasHurt = true;

	if (Health < 0.00f)
		Die();
	
}

void AFightGameCharacter::CheckCollision()
{

	/*if (OtherPlayer->getUpperPartHurtbox() && Health > 0) {
		if (Hitbox->IsOverlappingActor(OtherPlayer->getUpperPartHurtbox()))
		{
			OtherPlayer->setDamageZone(EDamageZones::UpperPart);
			OtherPlayer->ApplyDamage(Hitbox->getDamage());
		}
		else if (OtherPlayer->getHeadHurtbox())
		{
			if (Hitbox->IsOverlappingActor(OtherPlayer->getHeadHurtbox()))
			{
				OtherPlayer->setDamageZone(EDamageZones::Head);
				OtherPlayer->ApplyDamage(Hitbox->getDamage());
			}
		}
	}*/

	if (OtherPlayer->getCollisionCapsule() && Health > 0)
	{
		if (OtherPlayer->getCollisionCapsule()->IsOverlappingActor(Hitbox))
		{
			OtherPlayer->setDamageZone(EDamageZones::UpperPart);
			OtherPlayer->ApplyDamage(Hitbox->getDamage());
		}
	}
}

void AFightGameCharacter::HitByProjectile(float Damage)
{
	setDamageZone(EDamageZones::UpperPart);
	ApplyDamage(Damage);
}

void AFightGameCharacter::Die()
{
	UpperPartHurtbox->Reset();
	HeadHurtbox->Reset();
	Health = 0.00f;
}

void AFightGameCharacter::ChangeBoxesVisibility()
{
	bool Hidden;

	if (UpperPartHurtbox->IsHidden())
		Hidden = false;
	else
		Hidden = true;

	UpperPartHurtbox->SetActorHiddenInGame(Hidden);
	HeadHurtbox->SetActorHiddenInGame(Hidden);
	Hitbox->SetActorHiddenInGame(Hidden);

	OtherPlayer->getUpperPartHurtbox()->SetActorHiddenInGame(Hidden);
	OtherPlayer->getHeadHurtbox()->SetActorHiddenInGame(Hidden);
	OtherPlayer->getHitbox()->SetActorHiddenInGame(Hidden);
}

void AFightGameCharacter::KillPlayer(int PlayerNumber)
{
	if (PlayerNumber == 1)
	{
		if (isPlayer1)
			Die();
		else
			OtherPlayer->Die();
	}
	else
	{
		if (!isPlayer1)
			Die();
		else
			OtherPlayer->Die();
	}
}



