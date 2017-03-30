/**
    BuildingEscape
    Toucher.cpp

    Purpose: Toucher class is represents a component of the DefaultPawn.
             It is used to interact with objects/triggers found in the level.
             NOTE: This class is very simmilar to the Grabber class and is possible to create one
             combined class.

    @author Borislav Mutev
    @version 1.0 3/3/2017
*/

#include "BuildingEscape.h"
#include "Toucher.h"
#include "TriggerObject.h"


// Sets default values for this component's properties
UToucher::UToucher()
{
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UToucher::BeginPlay()
{
	Super::BeginPlay();

    SetupInputComponent();
	
}


// Called every frame
void UToucher::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

}

// Look for attached Input component (only appears at run time)
void UToucher::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        InputComponent->BindAction("Touch", IE_Pressed, this, &UToucher::Touch);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input component."), *GetOwner()->GetName());
    }
}

FVector UToucher::FindReachLineStart()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    return PlayerViewPointLocation;
}

FVector UToucher::CalcReachLineEnd()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    return PlayerViewPointLocation + (Reach * PlayerViewPointRotation.Vector());
}

const FHitResult UToucher::FindFirstStaticBodyInReach()
{
    /// Ray-cast(Line-Trace) out to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult,
        FindReachLineStart(),
        CalcReachLineEnd(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
        TraceParameters
    );

    return HitResult;
}

void UToucher::Touch()
{
    // LINE TRACE and reach any actors with physics body collision channel set
    auto HitResult = FindFirstStaticBodyInReach();
    auto ActorHit = HitResult.GetActor();

    UE_LOG(LogTemp, Warning, TEXT("Touch initiated."), *GetOwner()->GetName());

    if (ActorHit && ActorHit->ActorHasTag("DoorTrigger"))
    {
        UE_LOG(LogTemp, Warning, TEXT("Touched %s trigger."), *GetOwner()->GetName());
        Cast<ATriggerObject>(ActorHit)->Toggle();
    }
}
