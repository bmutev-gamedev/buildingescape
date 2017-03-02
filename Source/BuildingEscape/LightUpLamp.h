// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "LightUpLamp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLightUpEvent);

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
	
    AActor* Owner = nullptr;

    bool DetectActorPresence();
};
