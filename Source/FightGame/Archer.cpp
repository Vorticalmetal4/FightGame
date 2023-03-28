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

	MediumAttackHitbox.SetLocation({ 0.0f, 100.0f, 20.0f });
	MediumAttackHitbox.SetScale3D({ 0.3f, 0.9f, 0.6f });

	HardAttackHitbox.SetLocation({ 0.0f, 65.0f, 0.0f });
	HardAttackHitbox.SetScale3D({ 0.3f, 0.7f, 1.2f });

	FirstComboHitbox.SetLocation({0.0f, 100.0f, 10.0f});
	FirstComboHitbox.SetScale3D({0.3f, 1.0f, 0.5f});

	//Capsule Transforms
	CapsuleTransform.SetScale3D({ 1.5f, 1.7f, 2.1f });
	CapsuleTransform.SetLocation({ 0.0f, 0.0f, -15.0f });
	BlockingCapsuleTransform.SetScale3D({ 1.0f, 2.8f, 1.8f });
	BlockingCapsuleTransform.SetLocation({ 0.0f, 0.0f, -30.0f });
	CrouchingCapsuleTransform.SetScale3D({ 1.5f, 2.0f, 1.3f });
	CrouchingCapsuleTransform.SetLocation({ 0.0f, 0.0f, -35.0f });
	BlockingCrouchedCapsuleTransform.SetScale3D({ 2.0f, 3.0f, 1.3f });
	BlockingCrouchedCapsuleTransform.SetLocation(CrouchingCapsuleTransform.GetLocation());
	AuxBlockigCrouchedCapsuleTransform = 45.0f;

	//SetHurtbox Transformations

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

	//Attack Force
	LightAttackForce = { 0.0f, 20.0f, 0.0f };
	MediumAttackForce = { 0.0f, 75.0f, 0.0f };
	HardAttackForce = { 0.0f, 100.0f, 0.0f };
	FirstComboForce = {0.0f, 175.0f, 0.0f};

	//Combos
	FirstCombo[0] = EAttack::None;
	FirstCombo[1] = EAttack::Light;
	FirstCombo[2] = EAttack::Back;
	FirstCombo[3] = EAttack::Light;
}
