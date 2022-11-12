// Fill out your copyright notice in the Description page of Project Settings.


#include "Archer.h"

AArcher::AArcher()
	:ArrowsVelocity(600.0f),
	Arrow(nullptr),
	ArrowsMesh(nullptr)
{
	//Set Hitbox Transform for each attack
	LightAttackHitbox.SetLocation({ 0.0f, 100.0f, 0.0f });
	LightAttackHitbox.SetScale3D({ 0.3f, 0.93f, 0.5f });

	FrontLightAttackHitbox.SetLocation({ 0.0f, 30.0f, 0.0f });
	FrontLightAttackHitbox.SetScale3D({ 0.3f, 0.8f, 0.3f });

	MediumAttackHitbox.SetLocation({ 0.0f, 100.0f, 20.0f });
	MediumAttackHitbox.SetScale3D({ 0.3f, 0.9f, 0.6f });

	HardAttackHitbox.SetLocation({ 0.0f, 65.0f, 0.0f });
	HardAttackHitbox.SetScale3D({ 0.3f, 0.7f, 1.2f });

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

	//SetHurtbox Transformations
	StandUpHurtboxTransform.SetLocation({ 0.0f, 0.0f, -25.f });
	StandUpHurtboxTransform.SetScale3D({ 0.3f, 0.6f, 1.4f });

	CrouchingHurtboxTransform.SetLocation({ 0.0f, 0.0f, -48.0f });
	CrouchingHurtboxTransform.SetScale3D({ 0.3f, 0.9f, 0.7f });

	BlockingHurtboxTransform.SetLocation({ 10.0f, 0.0f, -40.0f });
	BlockingHurtboxTransform.SetScale3D({ 0.3f, 1.0f, 1.2f });

	BlockingCrouchedHurtboxTransform.SetLocation({ 10.0f, 0.0f, -55.0f });
	BlockingCrouchedHurtboxTransform.SetScale3D({ 0.3f, 1.1f, 0.8f });

	HeadHurtboxTransform.SetLocation({ 10.0f, 0.0f, 60.0f });
	HeadHurtboxTransform.SetScale3D({ 0.3f, 0.28f, 0.3f });
	FlippedHeadHurtboxLocation = { -10.0f, 0.0f, 60.0f };

	HeadCrouchingHurtboxLocation = { 15.0f, 0.0f, 0.0f };
	FlippedHeadCrouchingHurtboxLocation = { -25.0f, 0.0f, 0.0f };
	HeadBlockingHurtboxLocation = { 10.0f, 0.0f, 35.0f };
	FlippedHeadBlockingHurtboxLocation = { -10.0f, 0.0f, 35.0f };
	HeadBlockingCrouchedHurtboxLocation = { 25.0f, 0.0f, 0.0f };
	FlippedHeadBlockingCrouchedHurtboxLocation = { -25.0f, 0.0f, 0.0f };

	//Arrow Transform
	ArrowTransform.SetScale3D({ 0.1, 0.1, 0.1 });
	ArrowTransform.SetRotation({0.0f, 270.0f, 90.0f, 0.0f});
	ArrowTransform.SetLocation({ -500.0f, 0.0f, 0.0f });

	ArrowsHitboxScale = { 0.3f, 1.12f, 0.1f };
	AuxArrowPosition = { 10.0f, -27.0f, 135.0f };
}
