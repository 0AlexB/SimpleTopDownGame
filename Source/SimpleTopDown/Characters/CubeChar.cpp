#include "CubeChar.h"
#include "Components/InputComponent.h"
#include "SimpleTopDown/Components/WeaponComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"

ACubeChar::ACubeChar()
{
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;

	bUseControllerRotationYaw = true;

	GetCharacterMovement()->SetIsReplicated(true);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArm);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
}

void ACubeChar::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACubeChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MouseInput();

}

void ACubeChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Up"), this, &ACubeChar::InputUp);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &ACubeChar::InputRight);

	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ACubeChar::InputFireOn);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Released, this, &ACubeChar::InputFireOff);
}

void ACubeChar::InputUp(float Value)
{
	AddMovementInput(FVector(Value, 0., 0.));
}

void ACubeChar::InputRight(float Value)
{
	AddMovementInput(FVector(0., Value, 0.));
}

void ACubeChar::InputFireOn()
{
	UWeaponComponent* Weapon = Cast<UWeaponComponent>(GetComponentByClass(UWeaponComponent::StaticClass()));
	if (Weapon)
		Weapon->Fire(true);
}

void ACubeChar::InputFireOff()
{
	UWeaponComponent* Weapon = Cast<UWeaponComponent>(GetComponentByClass(UWeaponComponent::StaticClass()));
	if (Weapon)
		Weapon->Fire(false);
}

void ACubeChar::MouseInput()
{
	APlayerController* PlController = Cast<APlayerController>(GetController());
	if (PlController)
	{
		FVector MousePos, MouseDir;
		if (PlController->DeprojectMousePositionToWorld(MousePos, MouseDir))
		{
			FRotator NewRotation = (MousePos + MouseDir * SpringArm->TargetArmLength - GetActorLocation()).GetSafeNormal2D().Rotation();
			PlController->SetControlRotation(NewRotation);
		}
	}
}

void ACubeChar::RotateToPoint_Implementation(FVector Point)
{
	FRotator NewRotation = (Point - GetActorLocation()).GetSafeNormal2D().Rotation();
	if (!NewRotation.Equals(GetActorRotation()))
		SetActorRotation(NewRotation);
}