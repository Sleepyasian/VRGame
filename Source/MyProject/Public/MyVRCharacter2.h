// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VRCharacter.h"
#include "Components/SphereComponent.h"
#include "MyVRCharacter2.generated.h"

/**
 *	
 */
class USphereComponent;

UCLASS()
class MYPROJECT_API AMyVRCharacter2 : public AVRCharacter
{
	GENERATED_BODY()

public:
	AMyVRCharacter2();
protected:
	void MoveForward(float Val);
	void MoveRight(float Val);

	void GripLeft();
	void GripRight();

	void HandleGrip(UGripMotionControllerComponent* MotionController);

	UFUNCTION(Server, Reliable, WithValidation)
	void Server_GripActor(UGripMotionControllerComponent* MotionController);

	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	bool bUseHMDForLocomotion;																

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	USphereComponent* LeftControllerCollision;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	USphereComponent* RightControllerCollision;

	public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
};
