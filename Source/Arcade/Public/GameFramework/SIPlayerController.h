// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SIPlayerController.generated.h"

UCLASS()
class ARCADE_API ASIPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACameraActor* MainCamera;
	
protected:
	virtual void BeginPlay() override;
};
