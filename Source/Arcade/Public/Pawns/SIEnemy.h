// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/SIPawn.h"
#include "SIEnemy.generated.h"

UCLASS()
class ARCADE_API ASIEnemy : public ASIPawn
{
	GENERATED_BODY()

public:
	ASIEnemy();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	virtual void Die() override;
	
};
