#pragma once

#include "TriggerObject.h"
#include "EndGameText.h"
#include "ChamberConsole.generated.h"

/**
 * ChamberConsole class is used to communicate with the forcefield, 
 * all lamps in the chamber room and the text tip above the console.
 * The Console monitors all lamps and controls them so that they can be 
 * switched ON or OFF based on the actions of the player.
 * Also it controls when the forcefield will be deactivated and 
 * what text will be displayer above it.
 *
 * @author Borislav Mutev
 * @version 1.1 30/3/2017
 */
UCLASS()
class BUILDINGESCAPE_API AChamberConsole : public ATriggerObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChamberConsole();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:
    UPROPERTY(EditAnywhere)
    ATriggerObject* LeftLampTrtigger = nullptr;

    UPROPERTY(EditAnywhere)
    ATriggerObject* RightLampTrigger = nullptr;

    UPROPERTY(EditAnywhere)
    ATriggerObject* BackLampTrigger  = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* SphereField              = nullptr;

    UPROPERTY(EditAnywhere)
    AActor* EndGameTxt               = nullptr;

    // Detect if the player has triggered/switched any lamps
    // and check if the sequence is right.
    void LampSequenceCheck();

    // Check if the force field should be deactivated.
    bool ShouldUnlockSphereField();

    // When the player has deactivated the lamps in wrong order
    // the UnlockSequence array is reseted with default values. 
    void ResetSequence();

    // When a wrong sequence of lamp switchining is made
    // the lamps are turned off.
    void TurnLampsOff();

    // Used with the text tip above the console in the chamber room.
    // Pitches the text a bit so it can be illuminated by the light.
    void RotateText(AEndGameText* EndGameText);

    bool IsSphereFieldLocked = true;

    static const int UnlockSequenceSize = 3;
    // Holds the temporary sequence of lamp triggering
    // Lamp numbering:
    //  LeftLampTrtigger = 0
    //  LeftLampTrtigger = 1
    //  BackLamTrigger   = 2
    int UnlockSequence[UnlockSequenceSize] = {};
};
