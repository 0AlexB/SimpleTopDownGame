// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SimpleTopDown/Projectiles/SphereProjectile.h"
#include "WeaponComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLETOPDOWN_API UWeaponComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	float FireCooldown = 1.;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASphereProjectile> ProjectileClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FVector ProjectileSpawnOffset = FVector(30., 0., 0.);

private:
	float FireCooldownCurrent = 0.f;
	bool bFireOn = false;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(NetMulticast, Reliable, WithValidation)
	void MulticastFire();

public:	
	UWeaponComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Server, Reliable, WithValidation)
	void Fire(bool bEnable);
};
