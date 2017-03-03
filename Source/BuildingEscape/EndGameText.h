/**
    BuildingEscape
    EndGameText.h

    Purpose: EndGameText class is used to create text in the level and control that text,
             displaying different string depending on the state of the level.  

    @course Borislav Mutev
    @version 1.0 3/3/2017
*/

#pragma once

#include "GameFramework/Actor.h"
#include "EndGameText.generated.h"

UCLASS()
class BUILDINGESCAPE_API AEndGameText : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEndGameText();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

    void UpdateText();

    void SetEndGameState(bool state);

private:
    UTextRenderComponent* EndGameText;
	bool IsEndGame = false;
};
