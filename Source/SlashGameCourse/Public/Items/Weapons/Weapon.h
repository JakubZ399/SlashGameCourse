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
	void PlayEquipSound();
	void DisableSphereCollision();
	void DeactivateEmbers();
	void Equip(USceneComponent* InParent, FName InSocketName, AActor* NewOwner, APawn* NewInstigator);
	void ExecuteGetHit(FHitResult BoxHit);
	bool ActorIsSameType(AActor* OtherActor);

	UPROPERTY(EditDefaultsOnly, Category = Weapon)
	EWeaponType WeaponType;

	TArray<AActor*> IgnoreActors;
	
protected:

	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnWeaponBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation);
	
private:

	void BoxTrace(FHitResult& BoxHit);
	
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* WeaponBox;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* StartTracePoint;
	UPROPERTY(VisibleAnywhere)
	USceneComponent* EndTracePoint;
	
	UPROPERTY(EditAnywhere, Category = WeaponAudio)
	USoundBase* EquipSound;

	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	float Damage = 20.f;


public:

	FORCEINLINE UBoxComponent* GetWeaponBox() const { return WeaponBox; }
};
