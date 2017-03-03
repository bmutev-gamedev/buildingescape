/**
    BuildingEscape
    ChamberDoorOpen.h

    Purpose: ChamberDoorOpen is a class for a component used with the door leading to the Chamber room.

    @course Borislav Mutev
    @version 1.0 3/3/2017
*/

#include "BuildingEscape.h"
#include "ChamberDoorOpen.h"
#include "ReactsOnTouch.h"

// Sets default values for this component's properties
UChamberDoorOpen::UChamberDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
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

bool ShouldOpenDoor()
{
    if (!LeftStatueTrigger)  { return; }
    if (!RightStatueTrigger) { return; }
    if (!LeftRockTrigger)    { return; }
    if (!RightRockTrigger)   { return; }

    IReactsOnTouch* TouchInterface = Cast<IReactsOnTouch>(LeftStatueTrigger);
    TriggersState[0] = TouchInterface->Execute_GetTriggerState (LeftStatueTrigger);

    TouchInterface = Cast<IReactsOnTouch>(RightStatueTrigger);
    TriggersState[1] = TouchInterface->Execute_GetTriggerState (RightStatueTrigger);

    TouchInterface = Cast<IReactsOnTouch>(LeftRockTrigger);
    TriggersState[2] = TouchInterface->Execute_GetTriggerState (LeftRockTrigger);

    TouchInterface = Cast<IReactsOnTouch>(RightRockTrigger);
    TriggersState[3] = TouchInterface->Execute_GetTriggerState (RightRockTrigger);

    // Open the door when all trigger are triggered
    if (TriggersState[0] && TriggersState[1] && TriggersState[2] && TriggersState[3])
    {
        return true;
    }
        
    return false;
}

