// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

class USoundBase;
class UBoxComponent;
class USpotLightComponent;

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	EOneHandedWeapon UMETA(DisplayName = "One-Handed Weapon"),
	ETwoHandedWeapon UMETA(DisplayName = "Two-Handed Weapon")
};

UCLASS()
class SLASHGAMECOURSE_API AWeapon : public AItem
{
	GENERATED_BODY()

public:

	AWeapon();

	void AttachMeshToSocket(USceneComponent* InParent, FName InSocketName);
	void Equip(USceneComponent* InParent, FName InSocketName);

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	EWeaponType WeaponType;

	TArray<AActor*> IgnoreActors;
	
protected:

	virtual void BeginPlay() override;
	
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	virtual void OnWeaponBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);
	
private:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* WeaponBox;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* StartTracePoint;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* EndTracePoint;
	
	UPROPERTY(VisibleAnywhere)
	USpotLightComponent* SpotlightItem;
	
	UPROPERTY(EditAnywhere, Category = WeaponAudio)
	USoundBase* EquipSound;


public:

	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
};
