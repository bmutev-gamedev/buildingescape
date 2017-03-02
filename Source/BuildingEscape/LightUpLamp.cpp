// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "LightUpLamp.h"

#define OUT

// Sets default values for this component's properties
ULightUpLamp::ULightUpLamp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightUpLamp::BeginPlay()
{
	Super::BeginPlay();

    Owner = GetOwner();

    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate."), *GetOwner()->GetName());
    }
	
}


// Called every frame
void ULightUpLamp::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    if (DetectActorPresence())
    {
        LightUp.Broadcast();
    }
    else
    {
        LightDown.Broadcast();
    }
}

bool ULightUpLamp::DetectActorPresence()
{
    TArray<AActor*> OverlappingActors;
    if (!PressurePlate) { return false; }

    PressurePlate->GetOverlappingActors(
        OUT OverlappingActors
    );

    if (OverlappingActors.Num() > 0)
    {
        return true;
    }

    return false;
}
