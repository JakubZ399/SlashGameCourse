#include "Items/Treasure.h"
#include "SlashCharacter.h"
#include "Kismet/GameplayStatics.h"


void ATreasure::BeginPlay()
{
	Super::BeginPlay();
}

void ATreasure::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IPickupInterface* PickupInterface = Cast<IPickupInterface>(OtherActor);
	
	if (PickupInterface)
	{
		PickupInterface->AddGold(this);
		if (PickUpSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());
		}
		Destroy();
	}
}
