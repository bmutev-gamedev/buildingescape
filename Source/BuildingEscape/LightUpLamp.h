#pragma once

#include "Components/ActorComponent.h"
#include "WallLamp.h"
#include "LightUpLamp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLightUpEvent);

/**
 *  LightUpLamp class represents a component used to switch ON and OFF the light
 *  of a lamp actor derived from the AWallLamp class. Also it is used to detect if a player 
 *  is present at the trigger volume associated with the lamp actor.
 *
 *
 *  @course Borislav Mutev
 *  @version 1.1 30/3/2017
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API ULightUpLamp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightUpLamp();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    UPROPERTY(BlueprintAssignable)
    FLightUpEvent LightUp;

    UPROPERTY(BlueprintAssignable)
    FLightUpEvent LightDown;

private:
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;

    AWallLamp* Owner = nullptr; 

    // TODO: Change to event driven implementation
    bool ShouldToggle = false;
};
