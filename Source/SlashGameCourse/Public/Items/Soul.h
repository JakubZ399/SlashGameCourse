// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Soul.generated.h"

/**
 * 
 */
UCLASS()
class SLASHGAMECOURSE_API ASoul : public AItem
{
	GENERATED_BODY()

public:
	ASoul();
	virtual void Tick(float DeltaSeconds) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:

	void Move(float DeltaSeconds);

	float BasePosition;

	UPROPERTY(EditDefaultsOnly, Category = Move)
	float Amplitude = 20.f;
	UPROPERTY(EditDefaultsOnly, Category = Move)
	float Frequency = 2.f;

	UPROPERTY(EditAnywhere)
	int32 Souls;

public:
	FORCEINLINE int32 GetSouls() const { return Souls; }
	FORCEINLINE void SetSouls(int32 NumberOfSouls) { Souls = NumberOfSouls; }
};
