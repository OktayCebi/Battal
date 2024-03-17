// Battal


#include "Input/BattalController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Characters/BattalCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Weapons/Axe_Shield.h"
#include "Items/Weapons/Dagger.h"
#include "Items/Weapons/WeaponBase.h"


ABattalController::ABattalController()
{
	DodgeMontageNumber = 0.f;
	EndDodgeTimeAmount = 0.67f;
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
	EnhancedInputComponent->BindAction(StopSprintAction, ETriggerEvent::Triggered, this, &ABattalController::StopSprint);
	EnhancedInputComponent->BindAction(DodgeAction, ETriggerEvent::Triggered, this, &ABattalController::Dodge);
	EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ABattalController::Interact);
	EnhancedInputComponent->BindAction(EquipDaggerAction, ETriggerEvent::Triggered, this, &ABattalController::EquipDagger);
	EnhancedInputComponent->BindAction(EquipAxeAction, ETriggerEvent::Triggered, this, &ABattalController::EquipAxe);
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
		const float Forward = ForwardDirection.Length();
		const float Right = RightDirection.Length();
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
	if (BattalCharacter)
	{
		BattalCharacter->GetCharacterMovement()->MaxWalkSpeed = 700.f;
	}
}

void ABattalController::StopSprint()
{
	if (BattalCharacter)
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
	BattalCharacter->SetActionState(LastActionState);
	GetWorldTimerManager().ClearTimer(DodgeTimerHandle);
	
	
}
////////////////DODGE SECTION///////////////////


////////////////INTERACT SECTION///////////////////
void ABattalController::Interact()
{
	if(BattalCharacter->OverlappingItem)
	{
		AWeaponBase* Weapon = Cast<AWeaponBase>(BattalCharacter->OverlappingItem);
		Weapon->PickedUp(BattalCharacter->GetMesh(), Weapon->HandSocketNameforBody, Weapon->HandSocketNameforSecondBody);
		BattalCharacter->SetWeaponStanceState(Weapon->SelfStance);
		BattalCharacter->SetCharacterState(ECharacterState::ECS_Equipped);
		BattalCharacter->SetWeapon(Weapon);
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
		Weapon->SecondBody->AttachToComponent(BattalCharacter->GetMesh(), TransformRules, Weapon->HandSocketNameforSecondBody);
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
		Weapon->SecondBody->AttachToComponent(BattalCharacter->GetMesh(), TransformRules, Weapon->SheatSocketNameforSecondBody);
		GetWorldTimerManager().ClearTimer(EquipHandle);
		EnableInput(this);
	}
}


void ABattalController::EquipDagger()
{
	if (ADagger* Dagger = Cast<ADagger>(BattalCharacter->Weapon))
	{
		if (UAnimInstance* AnimInstance = BattalCharacter->GetMesh()->GetAnimInstance())
		{
			if (BattalCharacter->GetWeaponStanceState() == EWeaponStanceState::EwS_CommonStance)
			{
				GetWorldTimerManager().SetTimer(EquipHandle, this, &ABattalController::EquipAttachFunction, Dagger->EquipSeconds);
				FName const DaggerSection;
				AnimInstance->Montage_Play(Dagger->EquipWeaponMontage);
				AnimInstance->Montage_JumpToSection(DaggerSection, Dagger->EquipWeaponMontage);
				BattalCharacter->SetWeaponStanceState(EWeaponStanceState::EwS_DaggerStance);
				BattalCharacter->SetCharacterState(ECharacterState::ECS_Equipped);
				BattalCharacter->SetWeapon(Dagger);
				DisableInput(this);
			}
			else if (BattalCharacter->GetWeaponStanceState() == EWeaponStanceState::EwS_DaggerStance)
			{
				GetWorldTimerManager().SetTimer(EquipHandle, this, &ABattalController::UnArmAttachFunction, Dagger->UnArmSeconds);
				FName const DaggerSection;
				AnimInstance->Montage_Play(Dagger->UnArmWeaponMontage);
				AnimInstance->Montage_JumpToSection(DaggerSection, Dagger->UnArmWeaponMontage);
				BattalCharacter->SetWeaponStanceState(EWeaponStanceState::EwS_CommonStance);
				BattalCharacter->SetCharacterState(ECharacterState::ECS_Armed);
				DisableInput(this);
			}
		
		}
	}
}

void ABattalController::EquipAxe()
{
	if (AAxe_Shield* Axe = Cast<AAxe_Shield>(BattalCharacter->Weapon))
	{
		if (UAnimInstance* AnimInstance = BattalCharacter->GetMesh()->GetAnimInstance())
		{
			if (BattalCharacter->GetWeaponStanceState() == EWeaponStanceState::EwS_CommonStance)
			{
				GetWorldTimerManager().SetTimer(EquipHandle, this, &ABattalController::EquipAttachFunction, Axe->EquipSeconds);
				AnimInstance->Montage_Play(Axe->EquipWeaponMontage);
				AnimInstance->Montage_JumpToSection(FName ("AxeSection"), Axe->EquipWeaponMontage);
				BattalCharacter->SetWeaponStanceState(EWeaponStanceState::EwS_AxeStance);
				BattalCharacter->SetCharacterState(ECharacterState::ECS_Equipped);
				BattalCharacter->SetWeapon(Axe);
				DisableInput(this);
			}
			else if (BattalCharacter->GetWeaponStanceState() == EWeaponStanceState::EwS_AxeStance)
			{
				GetWorldTimerManager().SetTimer(EquipHandle, this, &ABattalController::UnArmAttachFunction, Axe->UnArmSeconds);
				AnimInstance->Montage_Play(Axe->UnArmWeaponMontage);
				AnimInstance->Montage_JumpToSection(FName ("AxeSection"), Axe->UnArmWeaponMontage);
				BattalCharacter->SetWeaponStanceState(EWeaponStanceState::EwS_CommonStance);
				BattalCharacter->SetCharacterState(ECharacterState::ECS_Armed);
				DisableInput(this);
			}
		
		}
	}
}

///////////////EQUIP SECTION///////////////////
