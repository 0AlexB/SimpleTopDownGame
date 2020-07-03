#include "CubeSensingComponent.h"
#include "SimpleTopDown/Controllers/CubeAIController.h"

UCubeSensingComponent::UCubeSensingComponent()
{
	bOnlySensePlayers = true;

	OnSeePawn.AddDynamic(this, &UCubeSensingComponent::OnSeeCube);
}

void UCubeSensingComponent::OnSeeCube(APawn* Cube)
{
	ACubeAIController* CubeAI = Cast<ACubeAIController>(GetSensorController());
	if (CubeAI && GetOwner())
	{
		AActor* OldTarget = CubeAI->GetTarget();
		FVector OwnerLocation = GetOwner()->GetActorLocation();
		if (!OldTarget || OldTarget->IsPendingKill() || (OldTarget != Cube && ((Cube->GetActorLocation() - OwnerLocation).SizeSquared() < (OldTarget->GetActorLocation() - OwnerLocation).SizeSquared())))
		{
			CubeAI->SetTarget(Cube);
		}
	}
}