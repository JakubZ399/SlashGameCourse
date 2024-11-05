#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAttributeComponent;
class UAnimMontage;

UCLASS()
class SLASHGAMECOURSE_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:

	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	
protected:

	virtual void BeginPlay() override;
	virtual void Attack();
	virtual void Die();

	
	// Play montage
	
	virtual void PlayAttackMontage(UAnimMontage* AttackMontage);
	void PlayHitReactMontage(const FName& SectionName);
	void DirectionalHitReact(const FVector& ImpactPoint);

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();
	virtual bool CanAttack();
	
	UPROPERTY(VisibleAnywhere, Category = Weapon)
	AWeapon* EquippedWeapon;

	// Animation Montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackOneHandedMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackTwoHandedMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* HitReactMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* DeathMontage;

	// Components
	UPROPERTY(VisibleAnywhere, Category = Stats)
	UAttributeComponent* AttributeComponent;

	UPROPERTY(EditAnywhere, Category = Audio)
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* BloodParticle;
	
};
