// Fill out your copyright notice in the Description page of Project Settings.


#include "Knight.h"

AKnight::AKnight()
{
	//Set Hitbox Transform for each attack
	LightAttackHitbox.SetLocation({ 0.0f, 100.0f, 0.0f });
	LightAttackHitbox.SetScale3D({ 0.3f, 0.93f, 0.5f });

	MediumAttackHitbox.SetLocation({ 0.0f, 100.0f, 20.0f });
	MediumAttackHitbox.SetScale3D({ 0.3f, 1.2f, 0.8f });

	HardAttackHitbox.SetLocation({ 0.0f, 65.0f, 80.0f });
	HardAttackHitbox.SetScale3D({ 0.3f, 0.4f, 0.6f });

	FirstComboHitbox.SetLocation({0.0f, 75.0f, 0.0f});
	FirstComboHitbox.SetScale3D({0.3f, 0.75f, 2.0f});


	//Capsule Transforms
	CapsuleTransform.SetScale3D({ 0.5f, 1.5f, 2.0f });
	CapsuleTransform.SetLocation({ 0.0f, 0.0f, -10.0f });
	BlockingCapsuleTransform.SetScale3D({ 1.0f, 2.8f, 1.8f });
	BlockingCapsuleTransform.SetLocation({ 0.0f, 0.0f, -10.0f });
	CrouchingCapsuleTransform.SetScale3D({ 0.5f, 1.7f, 1.3f });
	CrouchingCapsuleTransform.SetLocation({ 0.0f, 0.0f, -35.0f });
	BlockingCrouchedCapsuleTransform.SetScale3D({ 2.0f, 3.0f, 1.3f });
	BlockingCrouchedCapsuleTransform.SetLocation(CrouchingCapsuleTransform.GetLocation());
	AuxBlockigCrouchedCapsuleTransform = 45.0f;


	HeadHurtboxTransform.SetLocation({ 5.0f, 0.0f, 65.f });
	HeadHurtboxTransform.SetScale3D({ 0.3f, 0.28f, 0.3f });
	FlippedHeadHurtboxLocation = { 0.0f, 0.0f, 65.f };

	HeadCrouchingHurtboxLocation = { 0.0f, 0.0f, 0.0f };
	FlippedHeadCrouchingHurtboxLocation = { 0.0f, 0.0f, 0.0f };
	HeadBlockingHurtboxLocation = { 10.0f, 0.0f, 40.0f };
	FlippedHeadBlockingHurtboxLocation = { -10.0f, 0.0f, 40.0f };
	HeadBlockingCrouchedHurtboxLocation = { 10.0f, 0.0f, 10.0f };
	FlippedHeadBlockingCrouchedHurtboxLocation = { -20.0f, 0.0f, 10.0f };

	LightAttackForce = { 0.0f, 50.0f, 0.0f };
	MediumAttackForce = { 0.0f, 75.0f, 0.0f };
	HardAttackForce = { 0.0f, 100.0f, 0.0f };
	FirstComboForce = { 0.0f, 125.0f, 0.0f };

	FirstCombo[0] = EAttack::None;
	FirstCombo[1] = EAttack::Light;
	FirstCombo[2] = EAttack::Front;
	FirstCombo[3] = EAttack::Hard;
}

void AKnight::SetParticlesLocationAux()
{

	if (!isCrouching)
		ParticlesLocationAux = { 0.0f , YParticlesLocationAux, ZParticlesLocationAux };
	else
		ParticlesLocationAux = { 0.0f, YParticlesLocationAuxCrouched, ZParticlesLocationAux };

	if (!isFlipped)
		ParticlesLocationAux = { 0.0f, -ParticlesLocationAux.Y, ParticlesLocationAux.Z };

}