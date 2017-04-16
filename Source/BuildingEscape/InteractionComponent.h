#pragma once

#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

/**
 * InteractionComponent class represents a component used to simulate grabbing.
 *
 * @course "The Unreal Engine Developer Course" at Udemy led by Ben Tristem and Sam Pattuzzi
 * @version 1.1 30/3/2017
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
    UInteractionComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	// How far ahead of the player can we reach in cm
    UPROPERTY(EditAnywhere)
    float Reach = 100.f;

    UPhysicsHandleComponent* PhysicsHandle = nullptr;

    UInputComponent* InputComponent = nullptr;

    // Setup (assumed) attached input component
    void SetupInputComponent();	

    // Ray-casst and grab what is in reach
    void Grab();

    // Called when grab is released
    void Release();

    // Ray-casst and touch what is in reach
    void Touch();

    // Find (assumed) attached physics handle
    void FindPhysicsComponent();

    // Get current start of reach line
    FVector FindReachLineStart();

    // Get current end of reach line
    FVector CalcReachLineEnd();

    // Return hit for first physics body in reach
    const FHitResult FindFirstPhysicsBodyInReach();

    // Return hit for first static body in reach
    const FHitResult FindFirstStaticBodyInReach();
};
