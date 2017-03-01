// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "Toucher.h"
#include "ReactsOnTouch.h"


// Sets default values for this component's properties
UToucher::UToucher()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
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

FVector UToucher::GetReachLineStart()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    return PlayerViewPointLocation;
}

FVector UToucher::GetReachLineEnd()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    return PlayerViewPointLocation + (Reach * PlayerViewPointRotation.Vector());
}

const FHitResult UToucher::GetFirstStaticBodyInReach()
{
    /// Ray-cast(Line-Trace) out to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult,
        GetReachLineStart(),
        GetReachLineEnd(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_WorldStatic),
        TraceParameters
    );

    return HitResult;
}

void UToucher::Touch()
{
    // LINE TRACE and reach any actors with physics body collision channel set
    auto HitResult = GetFirstStaticBodyInReach();
    auto ActorHit = HitResult.GetActor();

    UE_LOG(LogTemp, Warning, TEXT("Touch initiated."), *GetOwner()->GetName());

    if (ActorHit && ActorHit->ActorHasTag("DoorTrigger"))
    {
        IReactsOnTouch* TouchInterface = Cast<IReactsOnTouch>(ActorHit);
        if (TouchInterface)
        {
            UE_LOG(LogTemp, Warning, TEXT("Touched %s trigger."), *GetOwner()->GetName());
            TouchInterface->Execute_ActivateTrigger (ActorHit);
        }  
    }
}
