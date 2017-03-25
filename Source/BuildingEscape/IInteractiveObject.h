/**
    BuildingEscape
    IInteractiveObject.h

    Purpose: IInteractiveObject class is an interface used to give objects the ability to
             react on "touch" events.

    @author Borislav Mutev
    @version 1.0 3/3/2017
*/

#pragma once

#include "IInteractiveObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractiveObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class BUILDINGESCAPE_API IInteractiveObject
{
	GENERATED_IINTERFACE_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    bool GetTriggerState() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    void ActivateTrigger();	
};
