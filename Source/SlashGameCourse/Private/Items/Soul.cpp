// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Soul.h"

#include "Interfaces/PickupInterface.h"

ASoul::ASoul()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASoul::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	Move(DeltaSeconds);
}

void ASoul::BeginPlay()
{
	Super::BeginPlay();

	BasePosition = GetActorLocation().Z;
}

void ASoul::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
							UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	if (PickupInterface)
	{
		PickupInterface->AddSouls(this);
		Destroy();
	}
}

void ASoul::Move(float DeltaSeconds)
{
	float Time = GetWorld()->GetTimeSeconds();
	float ZOffset = FMath::Sin(Time * Frequency) * Amplitude;

	FVector CurrentLocation = GetActorLocation();
	CurrentLocation.Z = BasePosition + ZOffset;

	SetActorLocation(CurrentLocation);
}




