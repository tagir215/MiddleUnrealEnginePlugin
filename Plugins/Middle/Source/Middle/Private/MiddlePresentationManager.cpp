// Fill out your copyright notice in the Description page of Project Settings.


#include "MiddlePresentationManager.h"

// Sets default values
AMiddlePresentationManager::AMiddlePresentationManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMiddlePresentationManager::SetRuntimeEngine(MiddleEngineRuntime* engine) {
	this->Engine = engine;
}


// Called when the game starts or when spawned
void AMiddlePresentationManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMiddlePresentationManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Engine->Tick(GetWorld(), DeltaTime);
}

