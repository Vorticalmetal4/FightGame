// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Hitbox.h"
#include "FightGameCharacter.generated.h"

UENUM(BlueprintType)
enum class EMovementDirection : uint8
{
	NotMoving UMETA(DisplayName = "NotMoving"),
	Right UMETA(DisPlayName = "Moving Right"),
	Left UMETA(DisplayName =  "Moving Left"),
	Jumping UMETA(DisplayName = "Jumping")
};

enum class EPosition : uint8
{
	StandUp,
	Blocking,
	Crouched,
	BlockingCrouched
};

enum class EAttack : uint8
{
	None,
	Light,
	LightCrouched,
	Medium,
	Hard,
	Front,
	Back,
	Fail
};

UENUM(BlueprintType)
enum class EDamageZones : uint8
{
	NotHurt UMETA(DisplayName),
	Head UMETA(DisplayName = "Head"),
	UpperPart UMETA(DisplayName = "UpperPart")
};

UENUM(BlueprintType)
enum class ECombo : uint8
{
	None,
	FirstCombo,
};

UCLASS(Config=Game, PerObjectConfig)
class AFightGameCharacter : public ACharacter
{
	GENERATED_BODY()

	void Tick(float DeltaTime);

protected:

	/** Called for side to side input */
	void MoveRight(float Val);

	/** Handle touch inputs. */
	void TouchStarted(const ETouchIndex::Type FingerIndex, const FVector Location);

	/** Handle touch stop event. */
	void TouchStopped(const ETouchIndex::Type FingerIndex, const FVector Location);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

	virtual void Jump() override;
	virtual void StopJumping() override;
	
	void StartCrouchingKeyB();
	void StartCrouching();
	void StartCrouchingGp(float Value);
	void StopCrouching();

	UFUNCTION(BlueprintCallable)
	void ApplyDamage(float Damage);

	UFUNCTION(BlueprintCallable)
	void SetData(AFightGameCharacter* _OtherPLayer, bool _isPlayer1);

	UFUNCTION(BlueprintCallable)
	void CheckCollision();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	AHitbox* HeadHurtbox;

	UStaticMeshComponent* HeadMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	FTransform HitboxTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hitbox")
	AHitbox* Hitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCapsuleComponent* CollisionCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerReference")
	AFightGameCharacter* OtherPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerReference")
	bool isPlayer1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	bool wasHurt;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	EDamageZones DamageZone;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool wasAttackConected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool wasLightAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool wasMediumAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool wasHardAttackUsed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	bool isAttacking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float LightAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float LightCrouchingAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float MediumAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float HardAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float FirstComboDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isWalking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	EMovementDirection MovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isCrouching;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkingValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool isBlocking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool UsingGamepad;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float XPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	bool CanMove;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float WalkingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool canPlayNewAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool canStartSpecialAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	bool hasSpecialAnimationFinished;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
	void StartEntrance();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
	void EntranceFinished();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
	void StartVictorySequence();

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Animations")
	void VictorySequenceFinished();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	bool isFlipped;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FTransform Transform;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Transform")
	FVector Scale;
	
	UFUNCTION(Exec, Category = "Debugging")
	void ChangeBoxesHiddenInGame();

	UFUNCTION(Exec, Category = "Debugging")
	void KillPlayer(int PlayerNumber);

	UFUNCTION(Category = "Debugging")
	void Die();

	//Combo System
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combos")
	ECombo CurrentCombo;
	int i;
	int j;
	int ComboBufferSize;
	int CombosNumber;
	int CombosSize[1];
	float PositionMovementBegan;
	float AuxComboDistance;
	EAttack FirstCombo[4];
	EAttack ComboBuffer[3];
	EAttack* Combos[1];
	EAttack Aux1ComboBuffer;
	EAttack Aux2ComboBuffer;
	void CheckCombo();
	void CleanComboBuffer();

	EAttack* getCombo() { return Combos[0]; }

	void setDamageZone(EDamageZones _DamageZone) { DamageZone = _DamageZone; }

	//Hitbox Attack Position
	FTransform LightAttackHitbox;
	FTransform MediumAttackHitbox;
	FTransform HardAttackHitbox;
	FTransform FirstComboHitbox;

	FTransform CapsuleTransform;
	FTransform BlockingCapsuleTransform;
	FTransform CrouchingCapsuleTransform;
	FTransform BlockingCrouchedCapsuleTransform;
	float AuxBlockigCrouchedCapsuleTransform;

	FVector LightAttackForce;
	FVector MediumAttackForce;
	FVector HardAttackForce;
	FVector FirstComboForce;

	FTransform HeadHurtboxTransform;
	FVector FlippedHeadHurtboxLocation;
	FVector HeadCrouchingHurtboxLocation;
	FVector FlippedHeadCrouchingHurtboxLocation;
	FVector HeadBlockingHurtboxLocation; 
	FVector FlippedHeadBlockingHurtboxLocation;
	FVector HeadBlockingCrouchedHurtboxLocation;
	FVector FlippedHeadBlockingCrouchedHurtboxLocation;

	UCharacterMovementComponent* CharacterMovement;
	UCharacterMovementComponent* OtherPlayerMovement;
	USceneComponent* Mesh;

	EPosition CurrentPosition;

	void ChangeDirection();
	float getHealth() { return Health; }

	void LightAttack();
	void MediumAttack();
	void HardAttack();

	void Block();

	void SetCollisionPosition();

	void Pushed(FVector AttackForce);

public:
	AFightGameCharacter();
	FVector getLocation() { return GetActorLocation(); }
	AActor* getHeadHurtbox() { return HeadHurtbox; }
	AActor* getHitbox() { return Hitbox; }
	FVector* getAttackForce() { return Hitbox->getAttackForce(); }
	UCapsuleComponent* getCollisionCapsule() { return CollisionCapsule; }
	void HitByProjectile(float Damage);

};
