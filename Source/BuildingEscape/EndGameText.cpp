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