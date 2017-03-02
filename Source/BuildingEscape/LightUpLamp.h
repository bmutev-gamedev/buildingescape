// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "LampState.h"
#include "LightUpLamp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLightUpEvent);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API ULightUpLamp : public UActorComponent,  public ILampState
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

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    bool GetLampState();
    virtual bool GetLampState_Implementation() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    void SetLampState(bool LampState);
    virtual void SetLampState_Implementation(bool LampState) override;	

private:
    UPROPERTY(EditAnywhere)
    ATriggerVolume* PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* AdjacentLampTrtigger  = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* OppositeLamTrigger    = nullptr;
	
    AActor* Owner = nullptr;

    bool SwtichLightOn = false;

    bool DetectActorPresence();

    void SyncLampState();
};
