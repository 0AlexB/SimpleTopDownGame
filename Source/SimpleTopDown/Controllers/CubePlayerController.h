// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CubePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOPDOWN_API ACubePlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	FVector SpawnLocation;
	FRotator SpawnRotation;
	UClass* PawnClass = nullptr;
	
protected:
	virtual void OnPossess(APawn* aPawn) override;

	UFUNCTION()
	void OnPawnDestroyed(AActor* DestroyedActor);

};
