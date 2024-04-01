#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	ECS_Unarmed UMETA(DisplayName = "Unarmed"),
	ECS_Armed UMETA (DisplayName = "Armed"),
	ECS_Equipped UMETA (DisplayName = "Equipped"),
	ECS_Dead UMETA (DisplayName = "Dead")
};


UENUM(BlueprintType)
enum class EActionState : uint8
{
	Eas_Idling UMETA(DisplayName = "Idling"),
	Eas_Moving UMETA (DisplayName = "Moving"),
	Eas_Dodging UMETA (DisplayName = "Dodging"),
	Eas_Guarding UMETA (DisplayName = "Guarding"),
	Eas_Attacking UMETA (DisplayName = "Attacking"),
	Eas_Staggered UMETA (DisplayName = "Staggered")
};

UENUM(BlueprintType)
enum class EWeaponStanceState : uint8
{
	EwS_CommonStance UMETA(DisplayName = "CommonStance"),
	EwS_DaggerStance UMETA(DisplayName = "DaggerStance"),
	EwS_AxeStance UMETA (DisplayName = "AxeStance"),
	EwS_GreatSwordStance UMETA (DisplayName = "GreatSwordStance"),
	EwS_GuardStance UMETA (DisplayName = "GuardStance")
};