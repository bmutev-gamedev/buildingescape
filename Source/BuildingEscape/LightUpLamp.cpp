/**
    BuildingEscape
    LightUpLamp.cpp

    Purpose: LightUpLamp class represents a component used to switch ON and OFF the light
             of a lamp actor derived from the AWallLamp class. Also it is used to detect if a player 
             is present at the trigger volume associated with the lamp actor.


    @course Borislav Mutev
    @version 1.0 3/3/2017
*/

#include "BuildingEscape.h"
#include "LightUpLamp.h"

#define OUT

// Sets default values for this component's properties
ULightUpLamp::ULightUpLamp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightUpLamp::BeginPlay()
{
	Super::BeginPlay();
    
    Owner = Cast<AWallLamp>(GetOwner()); 
}


// Called every frame
void ULightUpLamp::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // Switch ON/OFF the lamp based on actor presence
    TArray<AActor*> OverlappingActors;
    if (!PressurePlate) { return; }

    PressurePlate->GetOverlappingActors(
        OUT OverlappingActors
    );

    if (OverlappingActors.Num() > 0)
    {
        if (!Owner->GetState())
        {
            Owner->ToggleState();
        }
    }

    // Switch ON/OFF the lamp based on lamp precense   
    if (Owner->GetState())
    {
        LightUp.Broadcast();
    }
    else
    {
        LightDown.Broadcast();     
    }
}