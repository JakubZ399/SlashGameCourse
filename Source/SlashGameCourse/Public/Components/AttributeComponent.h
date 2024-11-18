#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASHGAMECOURSE_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UAttributeComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = Stats)
	float Health;

	UPROPERTY(EditAnywhere, Category = Stats)
	float MaxHealth;

	UPROPERTY(EditDefaultsOnly, Category = Stats)
	int32 Gold;

	UPROPERTY(EditDefaultsOnly, Category = Stats)
	int32 Souls;

public:

	void RecieveDamage(float Damage);
	float GetHealthPercent();
	bool IsAlive();
	void AddSouls(int32 NumberOfSouls);
	void AddGold(int32 NumberOfGold);
	FORCEINLINE int32 GetGold() const { return Gold; }
	FORCEINLINE int32 GetSouls() const { return Souls; }
};
