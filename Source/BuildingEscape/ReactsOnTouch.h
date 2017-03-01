// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ReactsOnTouch.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReactsOnTouch : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class BUILDINGESCAPE_API IReactsOnTouch
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    bool GetTriggerState();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyCategory")
    void ActivateTrigger();	
};
