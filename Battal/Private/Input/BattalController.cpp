// Battal


#include "Input/BattalController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/BattalCharacter.h"
#include "Components/SphereComponent.h"
#include "Elements/Framework/TypedElementQueryBuilder.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Weapons/WeaponBase.h"


ABattalController::ABattalController()
{
	DodgeMontageNumber = 0.f;
	EndDodgeTimeAmount = 0.67f;
	WeaponIndex = 0;
	WasAttackSaved = false;
	LightAttackCounter = 0;
}

void ABattalController::BeginPlay()
{
	Super::BeginPlay();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		BattalCharacter = Cast<ABattalCharacter>(ControlledPawn);
	}

	check(PlayerContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(PlayerContext, 0);
	
}

void ABattalController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABattalController::Move);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ABattalController::ZeroDodgeMontageNumber);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABattalController::Look);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ABattalController::Sprint);
	EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ABattalController::StopSprint);
	EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ABattalController::Dodge);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ABattalController::Interact);
	EnhancedInputComponent->BindAction(EquipAction, ETriggerEvent::Triggered, this, &ABattalController::Equip);
	EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Triggered, this, &ABattalController::Guard);
	EnhancedInputComponent->BindAction(GuardAction, ETriggerEvent::Completed, this, &ABattalController::ExitGuard);
	EnhancedInputComponent->BindAction(LightAttackAction, ETriggerEvent::Triggered, this, &ABattalController::LightAttack);
}

////////////////MOVEMENT SECTION///////////////////
void ABattalController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);

		////////BENİM KOD//////////////
		ForVec = InputActionValue.Get<FVector2d>();
		if(BattalCharacter->GetCharacterMovement()->bOrientRotationToMovement != true)
		{
			if (ForVec.X > 0.5f && ForVec.X > ForVec.Y) {DodgeMontageNumber = 2.f, EndDodgeTimeAmount = 0.67f;}
			else if (ForVec.X < -0.5f && ForVec.X < ForVec.Y) {DodgeMontageNumber = 1.f, EndDodgeTimeAmount = 0.67f;}
			else if (ForVec.Y < 0.f) {DodgeMontageNumber = 3.f, EndDodgeTimeAmount = 1.1f;}
			else
			{
				DodgeMontageNumber = 0.f, EndDodgeTimeAmount = 0.67f;
			}
			
		}
	}
	
}

void ABattalController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2d LookAxisValue = InputActionValue.Get<FVector2d>();
	AddYawInput(LookAxisValue.X * 0.3f);
	AddPitchInput(LookAxisValue.Y * 0.3f);
	
}

void ABattalController::Sprint()
{
	if (BattalCharacter && BattalCharacter->GetActionState() != EActionState::Eas_Guarding)
	{
		BattalCharacter->GetCharacterMovement()->MaxWalkSpeed = 700.f;
	}
}

void ABattalController::StopSprint()
{
	if (BattalCharacter->GetActionState() == EActionState::Eas_Guarding)
	{
		BattalCharacter->GetCharacterMovement()->MaxWalkSpeed = 200.f;
	}
	else if(BattalCharacter)
	{
		BattalCharacter->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	}
}
////////////////MOVEMENT SECTION///////////////////


////////////////DODGE SECTION///////////////////
void ABattalController::ZeroDodgeMontageNumber()
{
	DodgeMontageNumber = 0.f;
	ForVec.X = 0.f;
	ForVec.Y = 0.f;
}

void ABattalController::Dodge()
{
	if (CanDodgeWithWeapon())
	{
		LastActionState = BattalCharacter->GetLastActionState();
		BattalCharacter->SetActionState(EActionState::Eas_Dodging);
		GetWorldTimerManager().SetTimer(DodgeTimerHandle, this, &ABattalController::EndDodge, EndDodgeTimeAmount);
	
		if (UAnimInstance* AnimInstance = BattalCharacter->GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(BattalCharacter->Weapon->DodgeMontage);
			FName SectionName = FName();
			switch (DodgeMontageNumber)
			{
			case 0:
				SectionName = FName("Forward");
				break;
			case 1:
				SectionName = FName("Left");
				break;
			case 2:
				SectionName = FName("Right");
				break;
			case 3:
				SectionName = FName("Back");
				break;
			default:
				SectionName = FName("Back");
				break;
			}
			AnimInstance->Montage_JumpToSection(SectionName, BattalCharacter->Weapon->DodgeMontage);
		
		}
	}
	else if (CanDodge())
	{
		LastActionState = BattalCharacter->GetLastActionState();
		BattalCharacter->SetActionState(EActionState::Eas_Dodging);
		GetWorldTimerManager().SetTimer(DodgeTimerHandle, this, &ABattalController::EndDodge, EndDodgeTimeAmount);
	
		if (UAnimInstance* AnimInstance = BattalCharacter->GetMesh()->GetAnimInstance())
		{
			AnimInstance->Montage_Play(BattalCharacter->DodgeMontage);
			FName SectionName = FName();
			switch (DodgeMontageNumber)
			{
			case 0:
				SectionName = FName("Forward");
				break;
			case 1:
				SectionName = FName("Left");
				break;
			case 2:
				SectionName = FName("Right");
				break;
			case 3:
				SectionName = FName("Back");
				break;
			default:
				SectionName = FName("Back");
				break;
			}
			AnimInstance->Montage_JumpToSection(SectionName, BattalCharacter->DodgeMontage);
		
		}
	}
}

void ABattalController::EndDodge()
{
	if(LastActionState == EActionState::Eas_Guarding && BattalCharacter->IsGuarding == false)
	{
		BattalCharacter->SetActionState(EActionState::Eas_Idling);
		LastActionState = EActionState::Eas_Idling;
		GetWorldTimerManager().ClearTimer(DodgeTimerHandle);
	}
	else
	{
		BattalCharacter->SetActionState(LastActionState);
		GetWorldTimerManager().ClearTimer(DodgeTimerHandle);
	}
	
	
	
}
////////////////DODGE SECTION///////////////////


////////////////INTERACT SECTION///////////////////
void ABattalController::Interact()
{
	if(BattalCharacter->OverlappingItem)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(BattalCharacter->OverlappingItem);

		if(BattalCharacter->GetWeaponStanceState() != EWeaponStanceState::EwS_CommonStance)
		{
			Weapon->PickedUp(BattalCharacter->GetMesh(), Weapon->SheatSocketNameforBody, Weapon->SheatSocketNameforSecondBody);
			BattalCharacter->Weapons.AddUnique(Weapon);
		}
		else
		{
			Weapon->PickedUp(BattalCharacter->GetMesh(), Weapon->HandSocketNameforBody, Weapon->HandSocketNameforSecondBody);
			BattalCharacter->SetWeaponStanceState(Weapon->SelfStance);
			BattalCharacter->SetCharacterState(ECharacterState::ECS_Equipped);
			BattalCharacter->SetWeapon(Weapon);
			BattalCharacter->Weapons.AddUnique(Weapon);
			BattalCharacter->Weapon->Sphere->DestroyComponent();
		}
		
	}
}
////////////////INTERACT SECTION///////////////////


///////////////EQUIP SECTION///////////////////
void ABattalController::EquipAttachFunction()
{
	if (AWeaponBase* Weapon = BattalCharacter->Weapon)
	{
		const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		Weapon->Body->AttachToComponent(BattalCharacter->GetMesh(), TransformRules, Weapon->HandSocketNameforBody);
		if(Weapon->SecondBody)
		{
			Weapon->SecondBody->AttachToComponent(BattalCharacter->GetMesh(), TransformRules, Weapon->HandSocketNameforSecondBody);
		}
		GetWorldTimerManager().ClearTimer(EquipHandle);
		EnableInput(this);
	}
}

void ABattalController::UnArmAttachFunction()
{
	if (AWeaponBase* Weapon = BattalCharacter->Weapon)
	{
		const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
		Weapon->Body->AttachToComponent(BattalCharacter->GetMesh(), TransformRules, Weapon->SheatSocketNameforBody);
		if(Weapon->SecondBody)
		{
			Weapon->SecondBody->AttachToComponent(BattalCharacter->GetMesh(), TransformRules, Weapon->SheatSocketNameforSecondBody);
		}
		GetWorldTimerManager().ClearTimer(EquipHandle);
		EnableInput(this);
	}
}

void ABattalController::Equip()
{
	if (UAnimInstance* AnimInstance = BattalCharacter->GetMesh()->GetAnimInstance())
	{
		if (WeaponIndex == BattalCharacter->Weapons.Num())
		{
			WeaponIndex = 0;
		}

		if(BattalCharacter->GetWeaponStanceState() != EWeaponStanceState::EwS_CommonStance && BattalCharacter->Weapon != nullptr)
		{
			GetWorldTimerManager().SetTimer(EquipHandle, this, &ABattalController::UnArmAttachFunction, BattalCharacter->Weapon->UnArmSeconds);
			AnimInstance->Montage_Play(BattalCharacter->Weapon->UnArmWeaponMontage);
			AnimInstance->Montage_JumpToSection(BattalCharacter->Weapon->EquipMontageSectionName, BattalCharacter->Weapon->UnArmWeaponMontage);
			BattalCharacter->SetWeaponStanceState(EWeaponStanceState::EwS_CommonStance);
			BattalCharacter->SetCharacterState(ECharacterState::ECS_Armed);
			DisableInput(this);
		}

		else if(BattalCharacter->Weapon != nullptr)
		{
			GetWorldTimerManager().SetTimer(EquipHandle, this, &ABattalController::EquipAttachFunction, BattalCharacter->Weapons[WeaponIndex]->EquipSeconds);
			AnimInstance->Montage_Play(BattalCharacter->Weapons[WeaponIndex]->EquipWeaponMontage);
			AnimInstance->Montage_JumpToSection(BattalCharacter->Weapons[WeaponIndex]->EquipMontageSectionName, BattalCharacter->Weapons[WeaponIndex]->EquipWeaponMontage);
			BattalCharacter->SetWeaponStanceState(BattalCharacter->Weapons[WeaponIndex]->SelfStance);
			BattalCharacter->SetCharacterState(ECharacterState::ECS_Equipped);
			BattalCharacter->SetWeapon(BattalCharacter->Weapons[WeaponIndex]);
			DisableInput(this);
			WeaponIndex++;
		}
	}
}

///////////////EQUIP SECTION///////////////////

//////////////GUARd SECTION///////////////////
void ABattalController::Guard()
{
	BattalCharacter->SetActionState(EActionState::Eas_Guarding);
	BattalCharacter->GetCharacterMovement()->MaxWalkSpeed = 200.f;
	BattalCharacter->IsGuarding = true;
}

void ABattalController::ExitGuard()
{
	BattalCharacter->SetActionState(EActionState::Eas_Idling);
	BattalCharacter->GetCharacterMovement()->MaxWalkSpeed = 500.f;
	BattalCharacter->IsGuarding = false;
}
//////////////GUARd SECTION///////////////////

///////////LIGHT ATTACK SECTION//////////////
void ABattalController::LightAttack()
{
	if (UAnimInstance* AnimInstance = BattalCharacter->GetMesh()->GetAnimInstance())
	{
		if(CanAttack() && BattalCharacter->GetCharacterState() == ECharacterState::ECS_Equipped)
		{
			BattalCharacter->SetActionState(EActionState::Eas_Attacking);
			LightAttackCounter++;
			AnimInstance->Montage_Play(BattalCharacter->Weapon->LightAttackMontage);
			FName SectionName = FName();
			switch (LightAttackCounter)
			{
			case 1 :
				SectionName = FName("Attack1");
				break;
			case 2:
				SectionName = FName("Attack2");
				break;
			case 3:
				SectionName = FName("Attack3");
				break;
			case 4:
				SectionName = FName("Attack4");
				break;
			default:
				SectionName = FName("Attack1");
				break;
			}
			AnimInstance->Montage_JumpToSection(SectionName, BattalCharacter->Weapon->LightAttackMontage);
		}
		if(CanAttack() && BattalCharacter->GetCharacterState() != ECharacterState::ECS_Equipped)
		{
			BattalCharacter->SetActionState(EActionState::Eas_Attacking);
			LightAttackCounter++;
			AnimInstance->Montage_Play(BattalCharacter->LightAttackMontage);
			FName SectionName = FName();
			switch (LightAttackCounter)
			{
			case 1 :
				SectionName = FName("Attack1");
				break;
			case 2:
				SectionName = FName("Attack2");
				break;
			case 3:
				SectionName = FName("Attack3");
				break;
			case 4:
				SectionName = FName("Attack4");
				break;
			default:
				SectionName = FName("Attack1");
				break;
			}
			AnimInstance->Montage_JumpToSection(SectionName, BattalCharacter->LightAttackMontage);
		}
	}
}
