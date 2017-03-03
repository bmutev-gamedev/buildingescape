/**
    BuildingEscape
    WallLamp.h

    Purpose: WallLamp class is representing the lamps found in the Chamber room.
             It is used to give a way to control a lamp externally through ILampState interface
             or internally, through a component.

    @author Borislav Mutev
    @version 1.0 3/3/2017
*/

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
	
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyCategory")
    bool GetIsActorPresent();
    virtual bool GetIsActorPresent_Implementation() override;	

    // Used to give the lamp state to components of the lamp.
    bool GetLampStateLocal();

    // Used to set the lamp state through components of the lamp.
    void SetLampStateLocal(bool LampState);

private:
    bool SwtichLightOn = false;
};
