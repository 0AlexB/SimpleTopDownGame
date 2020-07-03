#include "SphereProjectile.h"
#include "SimpleTopDown/Components/HealthComponent.h"

ASphereProjectile::ASphereProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = true;
	SetReplicateMovement(true);

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->OnComponentHit.AddDynamic(this, &ASphereProjectile::ProjectileHit);

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

void ASphereProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASphereProjectile::ProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (HasAuthority() && OtherActor)
	{
		UHealthComponent* HealthComp = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));
		if (HealthComp)
		{
			HealthComp->TakeDamage(Damage);
		}
		Destroy();
	}
	
}