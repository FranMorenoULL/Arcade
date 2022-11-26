// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/SIPlayer.h"

#include "Components/BoxComponent.h"

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

	BoxCollision->SetVisibility(false, true);
	// TODO: ocultar correctamente
}