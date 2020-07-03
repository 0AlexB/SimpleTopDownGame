#include "WeaponComponent.h"
#include "Engine/World.h"

UWeaponComponent::UWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
	SetIsReplicatedByDefault(true);
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetOwner() && GetOwner()->HasAuthority())
	{
		if (FireCooldownCurrent > 0.)
			FireCooldownCurrent -= DeltaTime;
		else if (bFireOn)
		{
			if (ProjectileClass)
			{
				FVector SpawnLocation = GetComponentTransform().TransformPosition(ProjectileSpawnOffset);
				FRotator SpawnRotation = GetComponentRotation();
				GetWorld()->SpawnActor(ProjectileClass, &SpawnLocation, &SpawnRotation);

				FireCooldownCurrent = FireCooldown;
				SetComponentTickEnabled(true);
			}
		}
		else
			SetComponentTickEnabled(false);
	}
}

bool UWeaponComponent::Fire_Validate(bool bEnable)
{
	return true;
}

void UWeaponComponent::Fire_Implementation(bool bEnable)
{
	bFireOn = bEnable;
	if (bEnable && !IsComponentTickEnabled())
		SetComponentTickEnabled(true);
}

bool UWeaponComponent::MulticastFire_Validate()
{
	return true;
}

void UWeaponComponent::MulticastFire_Implementation()
{
	//Ѕум! —юда бы звук и эффект, но у мен€ их нет.
}