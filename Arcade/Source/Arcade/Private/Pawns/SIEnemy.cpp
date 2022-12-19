// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/SIEnemy.h"

ASIEnemy::ASIEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	
	FireRate = 0.5f;
}

void ASIEnemy::BeginPlay()
{
	Super::BeginPlay();

	if (const UWorld* World = GetWorld())
	{
		FTimerHandle StartFiringTimerHandle;
		const float StartingFireRate = FMath::RandRange(0.01f, FireRate);
		World->GetTimerManager().SetTimer(StartFiringTimerHandle, this, &ASIPawn::StartFire, StartingFireRate);

		TargetHeight = OscillationHeight + FMath::RandRange(-OscillationAmplitude, OscillationAmplitude);
	}
}

void ASIEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveForward(1.f);
	const float HeightDifference = GetActorLocation().Z - TargetHeight;
	const float AbsHeightDifference = FMath::Abs(HeightDifference);
	const float CorrectionFactor = -OscillationStrength * (AbsHeightDifference / HeightDifference) * FMath::Sqrt(AbsHeightDifference / OscillationAmplitude);
	MoveRight(CorrectionFactor);
}

void ASIEnemy::Die()
{
	Super::Die();
	
	if (UWorld* World = GetWorld())
	{
		World->DestroyActor(this);
	}
}