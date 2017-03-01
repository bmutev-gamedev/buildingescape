// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "ChamberDoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChamberDoorEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UChamberDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UChamberDoorOpen();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    UPROPERTY(BlueprintAssignable)
    FChamberDoorEvent OnOpen;
	
private:
    UPROPERTY(EditAnywhere)
    AActor* LeftStatueTrigger  = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* RightStatueTrigger = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* LeftRockTrigger    = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* RightRockTrigger   = nullptr;

    bool TriggersState[4] = {};

};
