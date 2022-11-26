// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFramework/SIPlayerController.h"

#include "Camera/CameraActor.h"
#include "Camera/CameraComponent.h"


void ASIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainCamera = NewObject<ACameraActor>(this, ACameraActor::StaticClass());
	MainCamera->GetCameraComponent()->SetProjectionMode(ECameraProjectionMode::Orthographic);
	SetViewTarget(MainCamera);
}
