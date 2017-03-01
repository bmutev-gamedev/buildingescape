// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "DoorTrigger.h"


// Sets default values
ADoorTrigger::ADoorTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADoorTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoorTrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ADoorTrigger::GetTriggerState_Implementation()
{
    return IsTriggered;
}

void ADoorTrigger::ActivateTrigger_Implementation()
{
    IsTriggered = true;
}

