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

public:

	void RecieveDamage(float Damage);
	float GetHealthPercent();
};
