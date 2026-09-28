// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MiddleEngineRuntime.h"
#include <memory>
#include "MiddlePresentationManager.generated.h"

UCLASS()
class MIDDLE_API AMiddlePresentationManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMiddlePresentationManager();
	void SetRuntimeEngine(MiddleEngineRuntime* Engine);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	MiddleEngineRuntime* Engine;
};
