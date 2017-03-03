/**
    BuildingEscape
    OpenDoor.cpp

    Purpose: OpenDoor class represents a component used to controll a StaticMeshActor door object.

    @course "The Unreal Engine Developer Course" at Udemy led by Ben Tristem and Sam Pattuzzi
    @version 1.0 3/3/2017
*/

#include "BuildingEscape.h"
#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

    if (!PressurePlate)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing pressure plate."), *GetOwner()->GetName());
    }
}

// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    // Poll the Trigger Volume
    // If the ActorThatOpens is in the volume
    if (CalcTotalMassOnPlate() > TriggerMass)
    {
        OnOpen.Broadcast();
    }

    else 
    {
        OnClose.Broadcast();
    }

}

// Return total mass in kg
float UOpenDoor::CalcTotalMassOnPlate()
{
    float TotalMass = 0.f;

    // Find all the overlapping actors
    TArray<AActor*> OverlappingActors;
    if (!PressurePlate) { return TotalMass; }
    PressurePlate->GetOverlappingActors(
        OUT OverlappingActors
    );

    // Iterate through them adding their mass
    for (const auto& Actor : OverlappingActors) {
        TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
    }

    return TotalMass;
}
