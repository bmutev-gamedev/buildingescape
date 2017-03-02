// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LampState.h"
#include "WallLamp.generated.h"

UCLASS()
class BUILDINGESCAPE_API AWallLamp : public AActor, public ILampState
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWallLamp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    bool GetLampState();
    virtual bool GetLampState_Implementation() override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    void SetLampState(bool LampState);
    virtual void SetLampState_Implementation(bool LampState) override;	
	
    bool GetLampStateLocal();
    void SetLampStateLocal(bool LampState);

private:
    bool SwtichLightOn = false;
};
