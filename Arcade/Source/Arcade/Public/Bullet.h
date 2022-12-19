// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

class UBoxComponent;
class UHealthComponent;
class UNiagaraSystem;
class UProjectileMovementComponent;
class UStaticMeshComponent;

UCLASS()
class ARCADE_API ABullet : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* Box;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* Mesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UHealthComponent* Health;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* Movement;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* ExplosionNS;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundWave* ExplosionSW;
	
public:
	ABullet();

	void Fire(const float Speed) const;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	virtual void Die();

};
