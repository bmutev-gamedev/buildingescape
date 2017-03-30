/**
    BuildingEscape
    ChamberDoorOpen.h

    Purpose: ChamberDoorOpen is a class for a component used with the door leading to the Chamber room.

    @course Borislav Mutev
    @version 1.0 3/3/2017
*/

#include "BuildingEscape.h"
#include "ChamberDoorOpen.h"

// Sets default values for this component's properties
UChamberDoorOpen::UChamberDoorOpen()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UChamberDoorOpen::BeginPlay()
{
	Super::BeginPlay();

    if (!LeftStatueTrigger)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing LeftStatueTrigger."), *GetOwner()->GetName());
    }

    if (!RightStatueTrigger)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing RightStatueTrigger."), *GetOwner()->GetName());
    }

    if (!LeftRockTrigger)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing LeftRockTrigger."), *GetOwner()->GetName());
    }

    if (!RightRockTrigger)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing RightRockTrigger."), *GetOwner()->GetName());
    }
	
}


// Called every frame
void UChamberDoorOpen::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    if (ShouldOpenDoor())
    {
        OnOpen.Broadcast();
    }
}

bool UChamberDoorOpen::ShouldOpenDoor()
{
    if (!LeftStatueTrigger)  { return false; }
    if (!RightStatueTrigger) { return false; }
    if (!LeftRockTrigger)    { return false; }
    if (!RightRockTrigger)   { return false; }

    TriggersState[0] = LeftStatueTrigger->GetState();
    TriggersState[1] = RightStatueTrigger->GetState();
    TriggersState[2] = LeftRockTrigger->GetState();
    TriggersState[3] = RightRockTrigger->GetState();

    // Open the door when all trigger are triggered
    if (TriggersState[0] && TriggersState[1] && TriggersState[2] && TriggersState[3])
    {
        return true;
    }
        
    return false;
}

