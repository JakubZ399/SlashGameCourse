// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "CharacterTypes.h"
#include "Enemy.generated.h"

class UPawnSensingComponent;
class AAIController;
class UHealthBarComponent;
class UWidgetComponent;
class UAttributeComponent;
class UAnimMontage;

UCLASS()
class SLASHGAMECOURSE_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:

	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void DirectionalHitReact(const FVector& ImpactPoint);
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

protected:

	virtual void BeginPlay() override;
	void CheckCombatTarget();
	void CheckPatrolTarget();

	void PlayReactMontage(const FName& SectionName);
	void PlayDeathMontage();

	UPROPERTY(BlueprintReadWrite)
	EDeathPose DeathPose = EDeathPose::EDP_Alive;

	bool InTargetRange(AActor* Target, double Radius);
	void MoveToTarget(AActor* Target);
	AActor* ChoosePatrolTarget();

	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

private:

	/*
	 * Components
	 */

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;
	
	UPROPERTY(VisibleAnywhere, Category = Stats)
	UAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere, Category = Stats)
	UHealthBarComponent* HealthBarWidget;

	/**
	 * Animations
	 */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = Audio)
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* BloodParticle;

	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 500.f;

	UPROPERTY(EditAnywhere)
	double AttackRadius = 150.f;

	/**
	 * Navigation
	 */
	
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;
	
	FTimerHandle PatrolTimer;
	void PatrolTimerFinish();
	
	UPROPERTY()
	AAIController* EnemyController;

	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

public:	
	
};
