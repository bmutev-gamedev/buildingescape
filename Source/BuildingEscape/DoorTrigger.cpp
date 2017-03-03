/**
    BuildingEscape
    DoorTrigger.h

    Purpose: DoorTrigger is a base class for all objects in the level that are used as triggers 
             which are to react to "touch".

    @course Borislav Mutev
    @version 1.0 3/3/2017
*/

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

