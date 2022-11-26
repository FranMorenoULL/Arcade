// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/SIPawn.h"
#include "SIPlayer.generated.h"

UCLASS()
class ARCADE_API ASIPlayer : public ASIPawn
{
	GENERATED_BODY()
	
public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	virtual void Die() override;
};
