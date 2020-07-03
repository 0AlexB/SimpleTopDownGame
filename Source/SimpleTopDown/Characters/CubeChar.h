#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SimpleTopDown/Components/HealthComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "CubeChar.generated.h"

UCLASS()
class SIMPLETOPDOWN_API ACubeChar : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UCameraComponent* CameraComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	USpringArmComponent* SpringArm = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Components")
	UHealthComponent* HealthComponent = nullptr;

protected:
	virtual void BeginPlay() override;

	void InputUp(float Value);
	void InputRight(float Value);
	void MouseInput();

	UFUNCTION(Server, Unreliable)
	void RotateToPoint(FVector Point);

public:	
	ACubeChar();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void InputFireOn();
	void InputFireOff();

};
