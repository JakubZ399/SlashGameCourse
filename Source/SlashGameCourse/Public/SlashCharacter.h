#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "InputActionValue.h"

#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UGroomComponent;
class AItem;
class UAnimMontage;

UCLASS()
class SLASHGAMECOURSE_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveInput;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookInput;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpInput;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* EquipInput;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* AttackInput;

	//Calbacks for EnhancedInput
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EKeyPressed();
	void Attack();

	//Play montage functions
	void PlayAttackMontage();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	bool CanAttak();

private:

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraBoom;
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlapingItem;

	//Animation montages

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

public:

	FORCEINLINE void SetOverlapingItem(AItem* Item) { OverlapingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const {	return CharacterState; }
	
};

