/**
    BuildingEscape
    TriggerObject.h

    Purpose: TriggerObject is a base class for all objects in the level that are used as triggers 
             which are to react to "touch".

    @course Borislav Mutev
    @version 1.0 3/3/2017
*/

#pragma once

#include "GameFramework/Actor.h"
#include "IInteractiveObject.h"
#include "TriggerObject.generated.h"

UCLASS()
class BUILDINGESCAPE_API ATriggerObject : public AActor,  public IInteractiveObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
    ATriggerObject();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    bool GetTriggerState() const;
    virtual bool GetTriggerState_Implementation() const override;

    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    void ActivateTrigger();
    virtual void ActivateTrigger_Implementation() override;	

protected:
    bool IsTriggered = false;
};