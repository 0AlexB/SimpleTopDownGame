#include "Spawner.h"
#include "Engine/World.h"

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	bNetLoadOnClient = false;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
	RootComponent = SpawnArea;
	SpawnArea->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority() && SpawnClass)
	{
		SpawnCooldownCurrent -= DeltaTime;
		if (SpawnCooldownCurrent <= 0.)
		{
			SpawnCooldownCurrent = SpawnCooldown;
			FVector SpawnLocation = FMath::RandPointInBox(SpawnArea->Bounds.GetBox()); 
			FRotator SpawnRotation = GetActorRotation();
			GetWorld()->SpawnActor(SpawnClass, &SpawnLocation, &SpawnRotation);
		}
	}
}

