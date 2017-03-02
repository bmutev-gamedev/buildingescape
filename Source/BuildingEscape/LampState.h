// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LampState.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULampState : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class BUILDINGESCAPE_API ILampState
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    bool GetLampState();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    void SetLampState(bool LampState);

    //UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    //bool GetIsActorPresent();
	
};
