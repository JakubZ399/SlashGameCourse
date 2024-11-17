#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.h"
#include "InputActionValue.h"
#include "Characters/BaseCharacter.h"
#include "SlashCharacter.generated.h"

class USlashOverlay;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UGroomComponent;
class AItem;
class UAnimMontage;

UCLASS()
class SLASHGAMECOURSE_API ASlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Jump() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint, AActor* Hitter) override;

protected:
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void EKeyPressed();
	virtual void Attack() override;

	/** Combat */
	virtual bool CanAttack() override;
	virtual void AttackEnd() override;
	void PlayEquipMontage(FName SectionName);
	bool CanDisarm();
	bool CanArm();
	virtual void Die() override;
	
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToBack();
	UFUNCTION(BlueprintCallable)
	void AttachWeaponToHand();
	UFUNCTION(BlueprintCallable)
	void FinishEquip();
	UFUNCTION(BlueprintCallable)
	void HitReactEnd();

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

private:
	void InitializeSlashOverlay();
	void SetHUDHealth();
	
	/** Character Movement */
	
	UPROPERTY(EditDefaultsOnly)
	UCameraComponent* CameraBoom;
	
	UPROPERTY(EditDefaultsOnly)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Hair;
	
	UPROPERTY(VisibleAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;
	
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY()
	USlashOverlay* SlashOverlay;

public:
	FORCEINLINE void SetOverlapingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const {	return CharacterState; }
	FORCEINLINE EActionState GetActionState() const { return ActionState; }
};
