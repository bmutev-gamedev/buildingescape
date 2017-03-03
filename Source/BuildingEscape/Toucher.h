/**
    BuildingEscape
    Toucher.h

    Purpose: Toucher class represents a component of the DefaultPawn.
             It is used to interact with objects/triggers found in the level.
             NOTE: This class is very simmilar to the Grabber class and is possible to create one
             combined class.

    @author Borislav Mutev
    @version 1.0 3/3/2017
*/

#pragma once

#include "Components/ActorComponent.h"
#include "Toucher.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UToucher : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UToucher();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
    // How far ahead of the player can we reach in cm
    UPROPERTY(EditAnywhere)
    float Reach = 100.f;

    UInputComponent* InputComponent = nullptr;

    // Setup (assumed) attached input component
    void SetupInputComponent();	

    // Get current start of reach line
    FVector GetReachLineStart();

    // Get current end of reach line
    FVector GetReachLineEnd();

    // Return hit for first physics body in reach
    const FHitResult GetFirstStaticBodyInReach();

    // Ray-casst and touch what is in reach
    void Touch();
	
};
