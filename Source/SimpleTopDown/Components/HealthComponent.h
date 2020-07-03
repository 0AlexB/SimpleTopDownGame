#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLETOPDOWN_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Health")
	int32 Health = 3;

protected:
	virtual void BeginPlay() override;

public:
	UHealthComponent();

	UFUNCTION(Server, Reliable, WithValidation)
	void TakeDamage(int32 Damage);
};
