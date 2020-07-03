// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/PawnSensingComponent.h"
#include "CubeSensingComponent.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLETOPDOWN_API UCubeSensingComponent : public UPawnSensingComponent
{
	GENERATED_BODY()
	
public:
	UCubeSensingComponent();

	UFUNCTION()
	void OnSeeCube(APawn* Cube);
};
