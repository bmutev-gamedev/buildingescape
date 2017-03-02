// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "LampState.h"
#include "WallLamp.h"

// Sets default values
AWallLamp::AWallLamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWallLamp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWallLamp::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AWallLamp::GetLampState_Implementation()
{
    return SwtichLightOn;
}

void AWallLamp::SetLampState_Implementation(bool LampState)
{
    SwtichLightOn = LampState;
}

bool AWallLamp::GetLampStateLocal()
{
    return SwtichLightOn;
}

void AWallLamp::SetLampStateLocal(bool LampState)
{
    SwtichLightOn = LampState;
}