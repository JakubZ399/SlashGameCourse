// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Enemy.generated.h"

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

	void PlayReactMontage(const FName& SectionName);

private:

	UPROPERTY(VisibleAnywhere, Category = Stats)
	UAttributeComponent* AttributeComponent;

	UPROPERTY(VisibleAnywhere, Category = Stats)
	UHealthBarComponent* HealthBarWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, Category = Audio)
	USoundBase* HitSound;
	
	UPROPERTY(EditAnywhere, Category = Particle)
	UParticleSystem* BloodParticle;
	
public:	
	
};
