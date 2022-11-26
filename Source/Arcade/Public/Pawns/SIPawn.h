// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SIPawn.generated.h"

class ABullet;
class UBoxComponent;
class UFloatingPawnMovement;
class UHealthComponent;
class UNiagaraSystem;
class UScoreComponent;

UCLASS()
class ARCADE_API ASIPawn : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* BoxCollision;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UFloatingPawnMovement* Movement;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UScoreComponent* Score;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ABullet> BulletClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* ExplosionNS;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundWave* ExplosionSW;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundWave* FireSW;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BulletSpeed = 800.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FireRate = 0.1f;

	FTimerHandle ResetFireTimerHandle;

private:
	bool bCanFire = true;
	bool bWantsToFire = false;
	
public:
	ASIPawn();

	UFUNCTION()
	virtual void MoveForward(float Value);
	UFUNCTION()
	virtual void MoveRight(float Value);
	UFUNCTION()
	virtual void StartFire();
	UFUNCTION()
	virtual void StopFire();
	UFUNCTION()
	virtual void ResetFire();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void Die();

};
