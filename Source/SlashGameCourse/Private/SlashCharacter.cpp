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
		EnhancedInputComponent->BindAction(EquipInput, ETriggerEvent::Triggered, this, &ASlashCharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(AttackInput, ETriggerEvent::Triggered, this, &ASlashCharacter::Attack);
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
	if (ActionState == EActionState::EAS_Attacking) return;
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
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlapingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
	}

	CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
}

void ASlashCharacter::Attack()
{
	if (CanAttak())
	{
		PlayAttackMontage();
		ActionState = EActionState::EAS_Attacking;
	}
}

bool ASlashCharacter::CanAttak()
{
	return ActionState == EActionState::EAS_Unoccupied &&
		CharacterState != ECharacterState::ECS_Unequipped;
}

void ASlashCharacter::PlayAttackMontage()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		const int32 Selection = FMath::RandRange(0, 2);
		FName SectionName = FName();
		switch (Selection)
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

void ASlashCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_Unoccupied;
}
