// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/SIPawn.h"
#include "SIEnemy.generated.h"

UCLASS()
class ARCADE_API ASIEnemy : public ASIPawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float OscillationHeight = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin=0.1f))
	float OscillationAmplitude = 120.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(ClampMin=0.1f))
	float OscillationStrength = 0.4f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float TargetHeight;
	
public:
	ASIEnemy();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	
	virtual void Die() override;
	
};
