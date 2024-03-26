// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVRCharacter2.h"
#include "Components/SphereComponent.h"

AMyVRCharacter2::AMyVRCharacter2() {
	bUseHMDForLocomotion = false;

	LeftControllerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftControllerCollison"));
	LeftControllerCollision->SetupAttachment(LeftMotionController);

	RightControllerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightControllerCollison"));
	RightControllerCollision->SetupAttachment(RightMotionController);
}

void AMyVRCharacter2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &AMyVRCharacter2::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("Move_X", this, &AMyVRCharacter2::MoveForward);
	PlayerInputComponent->BindAxis("Move_Y", this, &AMyVRCharacter2::MoveRight);

	PlayerInputComponent->BindAction("Grip_Left", IE_Pressed, this, &AMyVRCharacter2:: GripLeft);
	PlayerInputComponent->BindAction("Grip_Right", IE_Pressed, this, &AMyVRCharacter2::GripRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	//PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	//PlayerInputComponent->BindAxis("TurnRate", this, &AMyVRCharacter2::TurnAtRate);
	//PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	//PlayerInputComponent->BindAxis("LookUpRate", this, &AMyVRCharacter2::LookUpAtRate);
}




void AMyVRCharacter2::MoveForward(float Val)
{
	if (Val != 0.0f)
	{
		FVector Direction;
		if (bUseHMDForLocomotion) {
			Direction = VRReplicatedCamera->GetForwardVector();

		}
		else
		{
			Direction = LeftMotionController->GetForwardVector();
		}
		// add movement in that direction
		AddMovementInput(Direction, Val);
	}
}
void AMyVRCharacter2::MoveRight(float Val)
{
	if (Val != 0.0f)
	{
		FVector Direction;
		if (bUseHMDForLocomotion) {
			Direction = VRReplicatedCamera->GetRightVector();

		}
		else
		{
			Direction = LeftMotionController->GetRightVector();
		}
		// add movement in that direction
		AddMovementInput(Direction, Val);
	}
}

void AMyVRCharacter2::GripRight()
{
	HandleGrip(RightMotionController);
	/*GEngine->AddOnScreenDebugMessage(-5, 2.0f, FColor::Red, "Right Grip");

	if (RightMotionController->HasGrippedObjects())
	{
		TArray<AActor*> Gripped;
		RightMotionController->GetGrippedActors(Gripped);
		for (AActor* Actor : Gripped)
		{
			if (Actor)
			{
				RightMotionController->DropActor(Actor, true);
			}
		}
	}
	else
	{


		TArray<AActor*> Overlapping;
		RightControllerCollision->GetOverlappingActors(Overlapping);
		for (AActor* Actor : Overlapping)
		{
			if (Actor && Actor != this)
			{
				FTransform offset = RightMotionController->GetComponentTransform();
				if (RightMotionController->GripObject(Actor, offset))
				{
					break;
				}
			}
		}
	}
	*/
}

void AMyVRCharacter2::HandleGrip(UGripMotionControllerComponent* MotionController)
{

	if (MotionController->HasGrippedObjects())
	{
		TArray<AActor*> Gripped;
		MotionController->GetGrippedActors(Gripped);
		for (AActor* Actor : Gripped)
		{
			if (Actor)
			{
				MotionController->DropActor(Actor, true);
			}
		}
	}
	else
	{


		TArray<AActor*> Overlapping;
		EControllerHand CurrentHand;
		MotionController->GetHandType (CurrentHand);
		switch (CurrentHand)
		{
		case EControllerHand::Left:LeftControllerCollision->GetOverlappingActors(Overlapping); break;
		case EControllerHand::Right:RightControllerCollision->GetOverlappingActors(Overlapping); break;
		}
		RightControllerCollision->GetOverlappingActors(Overlapping);
		for (AActor* Actor : Overlapping)
		{
			if (Actor )
			{
				FTransform offset = RightMotionController->GetComponentTransform();
				if (MotionController->GripObject(Actor, offset))
				{
					break;
				}
			}
		}
	}

}


void AMyVRCharacter2::GripLeft()
{
	HandleGrip(LeftMotionController);
	/*
	GEngine->AddOnScreenDebugMessage(-5, 2.0f, FColor::Blue, "Left Grip"); 
	
	if (LeftMotionController->HasGrippedObjects())
	{
		TArray<AActor*> Gripped;
		LeftMotionController->GetGrippedActors(Gripped);
		for (AActor* Actor : Gripped)
		{
			if (Actor)
			{
				LeftMotionController->DropActor(Actor, true);
			}
		}
	}
	else
	{


		TArray<AActor*> Overlapping;
		LeftControllerCollision->GetOverlappingActors(Overlapping);
		for (AActor* Actor : Overlapping)
		{
			if (Actor && Actor != this)
			{
				FTransform offset = LeftMotionController->GetComponentTransform();
				if (LeftMotionController->GripObject(Actor, offset))
				{
					GEngine->AddOnScreenDebugMessage(-5, 2.0f, FColor::Blue, "Left Grip" + Actor->GetName());
					break;
				}
			}
		}

	}
	*/
}

