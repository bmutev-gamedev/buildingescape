// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ReactsOnTouch.h"
#include "ChamberConsole.generated.h"

UCLASS()
class BUILDINGESCAPE_API AChamberConsole : public AActor, public IReactsOnTouch
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberConsole();

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

private:
    UPROPERTY(EditAnywhere)
    AActor* LeftLampTrtigger = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* RightLampTrigger  = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* BackLampTrigger   = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* SphereField      = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* EndGameTxt       = nullptr;

    void UpdateLighSequence();

    bool TryUnlockSphereField();

    void ResetSequence();

    void TurnLampsOff();

    bool IsTriggered = false;

    bool IsSphereFieldLocked = true;

    static const int UnlockSequenceSize = 3;
    // Holds the temporary sequence of lamp triggering
    // Lamp numbering:
    //  LeftLampTrtigger = 1
    //  LeftLampTrtigger = 2
    //  BackLamTrigger   = 3
    int UnlockSequence[UnlockSequenceSize] = {};
};
