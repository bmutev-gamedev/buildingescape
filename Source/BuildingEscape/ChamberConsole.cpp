/**
    BuildingEscape
    ChamberConsole.cpp

    Purpose: ChamberConsole class is used to communicate with the forcefield, 
             all lamps in the chamber room and the text tip above the console.
             The Console monitors all lamps and controls them so that they can be 
             switched ON or OFF based on the actions of the player.
             Also it controls when the forcefield will be deactivated and 
             what text will be displayer above it.

    @author Borislav Mutev
    @version 1.0 3/3/2017
*/

#include "BuildingEscape.h"
#include "ChamberConsole.h"
#include "EndGameText.h"

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

    if (!EndGameTxt)
    {
        UE_LOG(LogTemp, Error, TEXT("%s missing EndGameText."), *GetName());
    }

    ResetSequence();
}

// Called every frame
void AChamberConsole::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    if (!GetState())
    {
        LampSequenceCheck();
    }
    else
    {
        Cast<AEndGameText>(EndGameTxt)->SetEndGameState(true);
        RotateText(Cast<AEndGameText>(EndGameTxt));
    }
}

void AChamberConsole::LampSequenceCheck()
{
    if (!LeftLampTrtigger) { return; }
    if (!RightLampTrigger) { return; }
    if (!BackLampTrigger)  { return; }
    if (!SphereField)      { return; }

    // Keep track of triggered lamps
    static bool TriggeredLamps[3] = { false, false, false };

    // Lamps IDs
    const int LeftLampID  = 0;
    const int RightLampID = 1;
    const int BackLampID  = 2;

    static int count = 0;
    if (count < UnlockSequenceSize)
    {
        // Save which lamp was triggered in what sequence
        // If lamp should be switched ON and it has not been yet
        if (LeftLampTrtigger->GetState() && !TriggeredLamps[LeftLampID])
        {
            UE_LOG(LogTemp, Warning, TEXT("Cyan Light is on."));
            UnlockSequence[count++] = LeftLampID;
            TriggeredLamps[LeftLampID] = true;
        }

        // If lamp should be switched ON and it has not been yet
        if (RightLampTrigger->GetState() && !TriggeredLamps[RightLampID])
        {
            UE_LOG(LogTemp, Warning, TEXT("Yellow Light is on."));
            UnlockSequence[count++] = RightLampID;
            TriggeredLamps[RightLampID] = true;
        }

        // If lamp should be switched ON and it has not been yet
        if (BackLampTrigger->GetState() && !TriggeredLamps[BackLampID])
        {
            UE_LOG(LogTemp, Warning, TEXT("Red Light is on."));
            UnlockSequence[count++] = BackLampID;
            TriggeredLamps[BackLampID] = true;
        }
    }
    else
    {
        // Try to unlock the sphere when all light have been triggered.
        // If the sequence of triggering is not right reset the lights.
        // NOTE: The lamp which the player activated last will stay ON.
        if (ShouldUnlockSphereField())
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

bool AChamberConsole::ShouldUnlockSphereField()
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

// Reset the activation sequence of the lamps
void AChamberConsole::ResetSequence()
{
    UnlockSequence[0] = -1;
    UnlockSequence[1] = -1;
    UnlockSequence[2] = -1;
}

// Communicate through the ILampState interface to tell the lamps to switch OFF.
void AChamberConsole::TurnLampsOff()
{
    if (!LeftLampTrtigger) { return; }
    if (!RightLampTrigger) { return; }
    if (!BackLampTrigger)  { return; }

    if (LeftLampTrtigger->GetState())
    {
        LeftLampTrtigger->Toggle();
    }

    if (RightLampTrigger->GetState())
    {
        RightLampTrigger->Toggle();
    }

    if (BackLampTrigger->GetState())
    {
        BackLampTrigger->Toggle();
    }
}

// Rotate the text above the console towards the player.
void AChamberConsole::RotateText(AEndGameText * EndGameText)
{
    FVector PlayerViewPointLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
        OUT PlayerViewPointLocation,
        OUT PlayerViewPointRotation
    );

    FVector TextLocation = EndGameText->GetActorLocation();

    FVector vec = PlayerViewPointLocation - TextLocation;
    FRotator rot = FRotationMatrix::MakeFromX(vec).Rotator();

    // Pitch the text a bit so the spot light can illuminate it.
    FRotator TextRot = rot + FRotator(10.f, 0.f, 0.f);
    EndGameText->SetActorRotation(TextRot);
}
