// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "ChamberConsole.h"
#include "LampState.h"

// Sets default values
AChamberConsole::AChamberConsole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChamberConsole::BeginPlay()
{
	Super::BeginPlay();

    if (!LeftLampTrtigger)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing LeftLampTrtigger."), *GetName());
    }

    if (!RightLampTrigger)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing RightLamTrigger."), *GetName());
    }

    if (!BackLampTrigger)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing BackLamTrigger."), *GetName());
    }
    
    if (!SphereField)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing SphereField."), *GetName());
    }

    ResetSequence();
}

// Called every frame
void AChamberConsole::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    UpdateLighSequence();
}

void AChamberConsole::UpdateLighSequence()
{
    if (!LeftLampTrtigger) { return; }
    if (!RightLampTrigger)  { return; }
    if (!BackLampTrigger)   { return; }
    if (!SphereField)      { return; }

    ILampState* LeftLamp = Cast<ILampState>(LeftLampTrtigger);
    ILampState* RightLam = Cast<ILampState>(RightLampTrigger);
    ILampState* BackLam  = Cast<ILampState>(BackLampTrigger);

    // UnlockSequence[0] is reserved for checking purposes
    // so count starts from 1
    static int count = 0;

    // Keep track of triggered lamps
    static bool TriggeredLamps[3] = { false, false, false };

    // Lamps numbering
    const int LeftLampID  = 0;
    const int RightLampID = 1;
    const int BackLampID  = 2;

    // TODO: After lights reset the light that the player is at is activated right away
    // and it seems that it did not reset.
    if (count < UnlockSequenceSize)
    {
        // Save which lamp was triggered at what time
        // If state is true, i.e. the lamp is on and
        if (LeftLamp->Execute_GetLampState(LeftLampTrtigger) && !TriggeredLamps[LeftLampID])
        {
            UE_LOG(LogTemp, Warning, TEXT("Cyan Light is on."));
            UnlockSequence[count++] = LeftLampID;
            TriggeredLamps[LeftLampID] = true;
        }

        if (RightLam->Execute_GetLampState(RightLampTrigger) && !TriggeredLamps[RightLampID])
        {
            UE_LOG(LogTemp, Warning, TEXT("Red Light is on."));
            UnlockSequence[count++] = RightLampID;
            TriggeredLamps[RightLampID] = true;
        }

        if (BackLam->Execute_GetLampState(BackLampTrigger) && !TriggeredLamps[BackLampID])
        {
            UE_LOG(LogTemp, Warning, TEXT("Yellow Light is on."));
            UnlockSequence[count++] = BackLampID;
            TriggeredLamps[BackLampID] = true;
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("All Lights are on."));

        // Try to unlock the sphere when all light have been triggered.
        // If the sequence of triggering is not right reset lights.
        if (TryUnlockSphereField())
        {
            SphereField->SetActorHiddenInGame(true);
            SphereField->SetActorEnableCollision(false);
        }
        else
        {
            count = 0;
            ResetSequence();
            TurnLampsOff();

            TriggeredLamps[LeftLampID]  = false;
            TriggeredLamps[RightLampID] = false;
            TriggeredLamps[BackLampID]  = false;
        }
    }
}

bool AChamberConsole::TryUnlockSphereField()
{
    // Lamps numbering
    const int LeftLampID  = 0;
    const int RightLampID = 1;
    const int BackLampID  = 2;

    if (UnlockSequence[0] == LeftLampID &&
        UnlockSequence[1] == RightLampID &&
        UnlockSequence[2] == BackLampID
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AChamberConsole::ResetSequence()
{
    UnlockSequence[0] = -2;
    UnlockSequence[1] = -1;
    UnlockSequence[2] = -1;
    UnlockSequence[3] = -1;
}

void AChamberConsole::TurnLampsOff()
{
    if (!LeftLampTrtigger) { return; }
    if (!RightLampTrigger) { return; }
    if (!BackLampTrigger)  { return; }

    ILampState* LampInterface = Cast<ILampState>(LeftLampTrtigger);
    LampInterface->Execute_SetLampState(LeftLampTrtigger, false);

    LampInterface = Cast<ILampState>(RightLampTrigger);
    LampInterface->Execute_SetLampState(RightLampTrigger, false);

    LampInterface  = Cast<ILampState>(BackLampTrigger);
    LampInterface->Execute_SetLampState(BackLampTrigger, false);
}
