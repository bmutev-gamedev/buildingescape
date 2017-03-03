/**
    BuildingEscape
    ReactsOnTouch.h

    Purpose: ReactsOnTouch class is an interface used to give objects the ability to
             react on "touch" events.

    @author Borislav Mutev
    @version 1.0 3/3/2017
*/

#pragma once

#include "ReactsOnTouch.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReactsOnTouch : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class BUILDINGESCAPE_API IReactsOnTouch
{
	GENERATED_IINTERFACE_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    bool GetTriggerState();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    void ActivateTrigger();	
};
