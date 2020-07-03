#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SimpleTopDown/Characters/CubeChar.h"
#include "Components/BoxComponent.h"
#include "Spawner.generated.h"

UCLASS()
class SIMPLETOPDOWN_API ASpawner : public AActor
{
	GENERATED_BODY()
	
protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UBoxComponent* SpawnArea = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	float SpawnCooldown = 3.;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
	TSubclassOf<ACubeChar> SpawnClass = nullptr;

private:
	float SpawnCooldownCurrent = 3.;

protected:
	virtual void BeginPlay() override;

public:	
	ASpawner();

	virtual void Tick(float DeltaTime) override;

};
