/**
    BuildingEscape
    TriggerObject.h

    Purpose: TriggerObject is a base class for all objects in the level that are used as triggers 
             which are to react to "touch".

    @course Borislav Mutev
    @version 1.0 3/3/2017
*/

#include "BuildingEscape.h"
#include "TriggerObject.h"


// Sets default values
ATriggerObject::ATriggerObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATriggerObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATriggerObject::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ATriggerObject::GetTriggerState_Implementation() const
{
    return IsTriggered;
}

void ATriggerObject::ActivateTrigger_Implementation()
{
    IsTriggered = true;
}

