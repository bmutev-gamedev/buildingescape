// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ReactsOnTouch.h"
#include "DoorTrigger.generated.h"

UCLASS()
class BUILDINGESCAPE_API ADoorTrigger : public AActor,  public IReactsOnTouch
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorTrigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    bool GetTriggerState();
    virtual bool GetTriggerState_Implementation() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    void ActivateTrigger();
    virtual void ActivateTrigger_Implementation() override;	

protected:
    bool IsTriggered = false;
};
