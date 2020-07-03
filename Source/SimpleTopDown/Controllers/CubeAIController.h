#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SimpleTopDown/Components/CubeSensingComponent.h"
#include "CubeAIController.generated.h"

UCLASS()
class SIMPLETOPDOWN_API ACubeAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UCubeSensingComponent* CubeSensing = nullptr;

private:
	UPROPERTY()
	AActor* Target = nullptr;

public:
	ACubeAIController();

	virtual void Tick(float DeltaTime) override;

	void SetTarget(AActor* NewTarget);
	AActor* GetTarget();
};
