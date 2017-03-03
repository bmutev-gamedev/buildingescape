/**
    BuildingEscape
    LampState.h

    Purpose: LampState class is an interface used to give objects the ability to
    access and control the lamp state.

    @author Borislav Mutev
    @version 1.0 3/3/2017
*/

#pragma once

#include "LampState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULampState : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class BUILDINGESCAPE_API ILampState
{
	GENERATED_IINTERFACE_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    bool GetLampState() const;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    void SetLampState(bool LampState);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    bool GetIsActorPresent() const;
	
};
