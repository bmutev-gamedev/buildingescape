/**
    BuildingEscape
    WallLamp.h

    Purpose: WallLamp class is representing the lamps found in the Chamber room.
             It is used to give a way to control a lamp externally through ILampState interface
             or internally, through a component.

    @author Borislav Mutev
    @version 1.0 3/3/2017
*/

#pragma once

#include "GameFramework/Actor.h"
#include "TriggerObject.h"
#include "WallLamp.generated.h"

UCLASS()
class BUILDINGESCAPE_API AWallLamp : public ATriggerObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallLamp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    // Used to give the lamp state to components of the lamp.
    bool GetState() const;

    // Used to set the lamp state through components of the lamp.
    void ToggleState();

private:
    bool SwtichLightOn = false;
};
