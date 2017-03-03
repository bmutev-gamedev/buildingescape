/**
    BuildingEscape
    EndGameText.cpp

    Purpose: EndGameText class is used to create text in the level and control that text,
             displaying different string depending on the state of the level.  

    @course Borislav Mutev
    @version 1.0 3/3/2017
*/

#include "BuildingEscape.h"
#include "EndGameText.h"

#define LOCTEXT_NAMESPACE "BuildingEscape"

// Sets default values
AEndGameText::AEndGameText()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    EndGameText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("EndGameText"));
    EndGameText->SetText(
        FText(LOCTEXT("TipText", "Find a way to reach\n and click on the console."))
    );
    EndGameText->SetTextRenderColor(FColor::White);
    EndGameText->SetHorizontalAlignment(EHTA_Center);
    EndGameText->SetWorldSize(20.0f);
    RootComponent = EndGameText;
}

// Called when the game starts or when spawned
void AEndGameText::BeginPlay()
{
	Super::BeginPlay();
    UpdateText();
}

// Called every frame
void AEndGameText::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
    UpdateText();
}

void AEndGameText::UpdateText()
{
    if (IsEndGame)
    {
        EndGameText->SetText(
            FText(LOCTEXT("EndGame", "Congratulations!\n You have completed the level!"))
        );
    }
}

void AEndGameText::SetEndGameState(bool state)
{
    IsEndGame = state;
}

#undef LOCTEXT_NAMESPACE