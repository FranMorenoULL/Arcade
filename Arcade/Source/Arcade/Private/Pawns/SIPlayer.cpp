// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/SIPlayer.h"

#include "Components/BoxComponent.h"
#include "Components/ScoreComponent.h"
#include "UI/SIHUD.h"

void ASIPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Vertical", this, &ASIPawn::MoveForward);
	PlayerInputComponent->BindAxis("Horizontal", this, &ASIPawn::MoveRight);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ASIPawn::StartFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ASIPawn::StopFire);
}

void ASIPlayer::Die()
{
	Super::Die();

	if (BoxCollision)
	{
		BoxCollision->SetVisibility(false, true);
		BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		BoxCollision->OnComponentBeginOverlap.Clear();
	}
	StopFire();
	DisableInput(Cast<APlayerController>(GetController()));

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->SetInputMode(FInputModeUIOnly());
		PlayerController->SetShowMouseCursor(true);
		if (ASIHUD* HUD = Cast<ASIHUD>(PlayerController->GetHUD()))
		{
			HUD->EndGame(Score->GetScore());
		}
	}
}