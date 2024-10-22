#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class ATreasure;
class UGeometryCollectionComponent;

UCLASS()
class SLASHGAMECOURSE_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	

	ABreakableActor();
	virtual void Tick(float DeltaTime) override;

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere)
	UGeometryCollectionComponent* GeometryCollection;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* Capsule;

private:	
	
	UPROPERTY(EditDefaultsOnly, Category = Treasure)
	TArray<TSubclassOf<ATreasure>> TreasureClasses;

	bool bBroken = false;
};
