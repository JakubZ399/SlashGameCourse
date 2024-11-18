#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Treasure.generated.h"


UCLASS()
class SLASHGAMECOURSE_API ATreasure : public AItem
{
	GENERATED_BODY()

	
protected:

	virtual void BeginPlay() override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = Audio)
	USoundBase* PickUpSound;

	UPROPERTY(EditAnywhere, Category = Treasure)
	int32 Gold = 10.f;

public:

	FORCEINLINE int32 GetGold() const { return Gold; }
};
