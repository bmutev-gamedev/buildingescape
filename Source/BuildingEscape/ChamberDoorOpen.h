#pragma once

#include "TriggerObject.h"
#include "ChamberDoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChamberDoorEvent);

/** 
 * ChamberDoorOpen is a class for a component used with the door leading to the Chamber room.
 *
 * @course Borislav Mutev
 * @version 1.0 3/3/2017
 */
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
    ATriggerObject* LeftStatueTrigger  = nullptr;

    UPROPERTY(EditAnywhere)
    ATriggerObject* RightStatueTrigger = nullptr;

    UPROPERTY(EditAnywhere)
    ATriggerObject* LeftRockTrigger    = nullptr;

    UPROPERTY(EditAnywhere)
    ATriggerObject* RightRockTrigger   = nullptr;

    bool TriggersState[4] = {};

    bool ShouldOpenDoor();

};
