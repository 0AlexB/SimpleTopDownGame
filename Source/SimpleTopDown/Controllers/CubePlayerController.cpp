#include "CubePlayerController.h"
#include "Engine/World.h"

void ACubePlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	if (aPawn && HasAuthority())
	{
		SpawnLocation = aPawn->GetActorLocation();
		SpawnRotation = aPawn->GetActorRotation();
		PawnClass = aPawn->GetClass();
		aPawn->OnDestroyed.AddDynamic(this, &ACubePlayerController::OnPawnDestroyed);
	}
}

void ACubePlayerController::OnPawnDestroyed(AActor* DestroyedActor)
{
	UnPossess();
	APawn* NewPawn = Cast<APawn>(GetWorld()->SpawnActor(PawnClass, &SpawnLocation, &SpawnRotation));
	if (NewPawn)
		Possess(NewPawn);
}