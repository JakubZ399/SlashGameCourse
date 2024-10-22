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
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	
	if (SlashCharacter)
	{
		if (PickUpSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, PickUpSound, GetActorLocation());
		}
		
		Destroy();
	}
}
