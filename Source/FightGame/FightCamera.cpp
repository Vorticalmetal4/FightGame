// Fill out your copyright notice in the Description page of Project Settings.


#include "FightCamera.h"
#include "FightGameCharacter.h"
#include "Camera/CameraComponent.h"

void AFightCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (Player1Ref) {
		if (Player2Ref)
		{
			SetActorLocation({ XLocation, (Player1Ref->getLocation().Y + Player2Ref->getLocation().Y) / 2.0f, (Player1Ref->getLocation().Z + Player2Ref->getLocation().Z) / 2.0f });
			
			CameraZoom = abs(Player1Ref->getLocation().Y - Player2Ref->getLocation().Y) * 0.1f;
			
			if (CameraZoom < 60.0f)
				CameraZoom = 60.0f;
			else if (CameraZoom > 80.0f)
				CameraZoom = 80.0f;

			CameraC->SetFieldOfView(CameraZoom);
		}
		else
			UE_LOG(LogTemp, Warning, TEXT("Player 2 Ref has failed"));
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("Player 1 Ref has failed failed"));
	
	
}