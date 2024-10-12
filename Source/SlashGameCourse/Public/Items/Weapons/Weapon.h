// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;
class USpotLightComponent;

UCLASS()
class SLASHGAMECOURSE_API AWeapon : public AItem
{
	GENERATED_BODY()

public:

	AWeapon();
	void AttachMeshToSocket(USceneComponent* InParent, FName InSocketName);
	void Equip(USceneComponent* InParent, FName InSocketName);
	
protected:
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:

	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* SpotlightItem;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* WeaponBox;
	
	UPROPERTY(EditAnywhere, Category = WeaponAudio)
	USoundBase* EquipSound;
};
