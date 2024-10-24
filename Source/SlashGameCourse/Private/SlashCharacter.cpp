#include "SlashCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "GroomComponent.h"

#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"

ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	
	CameraBoom = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraBoom->SetupAttachment(SpringArmComponent);

	Hair = CreateDefaultSubobject<UGroomComponent>(TEXT("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");

	Eyebrows = CreateDefaultSubobject<UGroomComponent>(TEXT("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");

}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComponent->bUsePawnControlRotation = true;

	if (APlayerController*  PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
		}
	}
}

void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInput, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
		EnhancedInputComponent->BindAction(LookInput, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
		EnhancedInputComponent->BindAction(JumpInput, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(EquipInput, ETriggerEvent::Started, this, &ASlashCharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(AttackInput, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);
	}

}

void ASlashCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
	if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
		EquippedWeapon->IgnoreActors.Empty();
	}
}


void ASlashCharacter::Look(const FInputActionValue& Value)
{
	FVector2d LookValue = Value.Get<FVector2d>();
	float ValueX = LookValue.X;
	float ValueY = LookValue.Y;

	AddControllerYawInput(ValueX);
	AddControllerPitchInput(ValueY);
}

void ASlashCharacter::Move(const FInputActionValue& Value)
{
	if (ActionState != EActionState::EAS_Unoccupied) return;
	if (Controller)
	{
		FVector2d MoveValue = Value.Get<FVector2d>();
		float ValueX = MoveValue.X;
		float ValueY = MoveValue.Y;

		FRotator Rotation = GetControlRotation();
		FRotator YawRotation(0, Rotation.Yaw, 0);
	
		FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
		AddMovementInput(ForwardDirection, ValueY);
		AddMovementInput(RightDirection, ValueX);
	}
	
}

void ASlashCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	
	if (OverlappingWeapon && !EquippedWeapon)
	{
		if (OverlappingWeapon->WeaponType == EWeaponType::EOneHandedWeapon)
		{
			OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
			CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		}
		else if (OverlappingWeapon->WeaponType == EWeaponType::ETwoHandedWeapon)
		{
			OverlappingWeapon->Equip(GetMesh(), FName("TwoHandedSocket"), this, this);
			CharacterState = ECharacterState::ECS_EquippedTwoHandedWeapon;
		}
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
	}
	else
	{
		if (CanDisarm())
		{
			PlayEquipMontage(FName("Unequip"));
			CharacterState = ECharacterState::ECS_Unequipped;
			ActionState = EActionState::EAS_Equipping;
		}
		else if (CanArm())
		{
			PlayEquipMontage(FName("Equip"));
			ActionState = EActionState::EAS_Equipping;

			if (EquippedWeapon->WeaponType == EWeaponType::EOneHandedWeapon)
			{
				CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
			}
			else if (EquippedWeapon->WeaponType == EWeaponType::ETwoHandedWeapon)
			{
				CharacterState = ECharacterState::ECS_EquippedTwoHandedWeapon;
			}
			
			
		}
	}
	
}

void ASlashCharacter::Attack()
{
	if (CanAttak())
	{
		if (EquippedWeapon->WeaponType == EWeaponType::EOneHandedWeapon)
		{
			PlayAttackMontage(AttackOneHandedMontage);
		}
		else if (EquippedWeapon->WeaponType == EWeaponType::ETwoHandedWeapon)
		{
			PlayAttackMontage(AttackTwoHandedMontage);
		}
		ActionState = EActionState::EAS_Attacking;
	}
}

bool ASlashCharacter::CanAttak()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

bool ASlashCharacter::CanDisarm()
{
	return ActionState == EActionState::EAS_Unoccupied && 
		CharacterState != ECharacterState::ECS_Unequipped;
}
bool ASlashCharacter::CanArm()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState == ECharacterState::ECS_Unequipped && 
		EquippedWeapon;
}

void ASlashCharacter::Disarm()
{
	if (EquippedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("SpineSocket"));
	}
}

void ASlashCharacter::Arm()
{
	if (EquippedWeapon->WeaponType == EWeaponType::EOneHandedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("RightHandSocket"));
	}
	else if (EquippedWeapon->WeaponType == EWeaponType::ETwoHandedWeapon)
	{
		EquippedWeapon->AttachMeshToSocket(GetMesh(), FName("TwoHandedSocket"));
	}
}

void ASlashCharacter::FinishEquip()
{
	ActionState = EActionState::EAS_Unoccupied;
}

void ASlashCharacter::PlayAttackMontage(UAnimMontage* AttackMontage)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		if (EquippedWeapon->WeaponType == EWeaponType::EOneHandedWeapon)
		{
			AttackMontageSelection = FMath::RandRange(0, 2);
		}
		else if(EquippedWeapon->WeaponType == EWeaponType::ETwoHandedWeapon)
		{
			AttackMontageSelection = FMath::RandRange(0, 1);
		}
		FName SectionName = FName();
		switch (AttackMontageSelection)
		{
		case 0:
			SectionName = FName("Attack1");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		case 2:
			SectionName = FName("Attack3");
			break;
		default:
			break;
		}
		AnimInstance->Montage_JumpToSection(SectionName,AttackMontage);
	}
}

void ASlashCharacter::PlayEquipMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && EquipMontage)
	{
		AnimInstance->Montage_Play(EquipMontage);
		AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	}
}


void ASlashCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}
