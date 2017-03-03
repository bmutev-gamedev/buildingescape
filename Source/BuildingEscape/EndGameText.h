// Fill out your copyright notice in the Description page of Project Settings.

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
