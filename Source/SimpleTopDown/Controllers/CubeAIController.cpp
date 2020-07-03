#include "CubeAIController.h"
#include "Kismet/KismetMathLibrary.h"
#include "SimpleTopDown/Characters/CubeChar.h"

ACubeAIController::ACubeAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickInterval = 1.;
	CubeSensing = CreateDefaultSubobject<UCubeSensingComponent>(TEXT("CubeSensing"));
}

void ACubeAIController::SetTarget(AActor* NewTarget)
{
	Target = NewTarget;
}

AActor* ACubeAIController::GetTarget()
{
	return Target;
}

void ACubeAIController::Tick(float DeltaTime)
{
	if (Target)
	{
		MoveToActor(Target);
		
		ACubeChar* CubePawn = Cast<ACubeChar>(GetPawn());
		if (CubePawn)
		{
			FVector ToTarget = (Target->GetActorLocation() - CubePawn->GetActorLocation()).GetSafeNormal2D();
			CubePawn->InputFireOn();
			SetControlRotation(ToTarget.Rotation());
		}
	}
}