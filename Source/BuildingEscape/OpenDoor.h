#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorEvent);

/**
 * OpenDoor class represents a component used to controll a StaticMeshActor door object.
 * 
 * @course "The Unreal Engine Developer Course" at Udemy led by Ben Tristem and Sam Pattuzzi
 * @version 1.0 3/3/2017
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnOpen;

    UPROPERTY(BlueprintAssignable)
    FDoorEvent OnClose;

private:
    // Trigger volume that is to be used by this class.
    UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

    UPROPERTY(EditAnywhere)
    float TriggerMass = 35.0f;

    // Return total mass in kg
    float CalcTotalMassOnPlate();
};
