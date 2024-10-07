﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class L20240925_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	TObjectPtr<UBoxComponent> Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> Body;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> Movement;

	UFUNCTION()
	void ProcessOverlap(AActor* OverlappedActor, AActor* OtherActor);

	UFUNCTION(BlueprintCallable, meta=(displayName="블루프린트에서 사용하는 함수"))
	void MakeCPPCallBP(int32 Number);

	UFUNCTION(BlueprintImplementableEvent)
	void MakeBPCallCPP(int32 Number);

	UFUNCTION(BlueprintNativeEvent)
	void MakeBPToNativeCallCPP(int32 Number);
	void MakeBPToNativeCallCPP_Implementation(int32 Number);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	class UParticleSystem* ParticleTemplate;
};
