#include "BuildingEscape.h"
#include "InteractionComponent.h"
#include "TriggerObject.h"

#define OUT

// Sets default values for this component's properties
UInteractionComponent::UInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
    FindPhysicsComponent();
    SetupInputComponent();
}

// Called every frame
void UInteractionComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
    Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

    if (!PhysicsHandle) { return; }
    // If the physics handle is attached
    if (PhysicsHandle->GrabbedComponent)
    {
        // Move the object that we're holdin
        PhysicsHandle->SetTargetLocation(CalcReachLineEnd());
    }
}

// Look for attached Input component (only appears at run time)
void UInteractionComponent::SetupInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent)
    {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UInteractionComponent::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UInteractionComponent::Release);
        InputComponent->BindAction("Touch", IE_Pressed, this, &UInteractionComponent::Touch);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing Input component."), *GetOwner()->GetName());
    }
}

void UInteractionComponent::Grab()
{
    // LINE TRACE and reach any actors with physics body collision channel set
    auto HitResult = FindFirstPhysicsBodyInReach();
    auto ComponentToGrab = HitResult.GetComponent();
    auto ActorHit = HitResult.GetActor();

    // If we hit something then attach a physics handle
    if (ActorHit)
    {
        if (!PhysicsHandle) { return; }
        PhysicsHandle->GrabComponent(
            ComponentToGrab,
            NAME_None,
            ComponentToGrab->GetOwner()->GetActorLocation(),
            true // allow rotation
        );
    }
}

void UInteractionComponent::Release()
{
    if (!PhysicsHandle) { return; }
    PhysicsHandle->ReleaseComponent();
}

void UInteractionComponent::Touch()
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

//Look for attached Physics handle
void UInteractionComponent::FindPhysicsComponent()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing PhysicsHandle component."),
            *GetOwner()->GetName()
        );
    }
}

FVector UInteractionComponent::FindReachLineStart()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    return PlayerViewPointLocation;
}

FVector UInteractionComponent::CalcReachLineEnd()
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    return PlayerViewPointLocation + (Reach * PlayerViewPointRotation.Vector());
}

const FHitResult UInteractionComponent::FindFirstPhysicsBodyInReach()
{
    /// Ray-cast(Line-Trace) out to reach distance
    FHitResult HitResult;
    FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
    
    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult,
        FindReachLineStart(),
        CalcReachLineEnd(),
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
        TraceParameters
    );

    return HitResult;
}

const FHitResult UInteractionComponent::FindFirstStaticBodyInReach()
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