#include "Characters/SlashAnimInstance.h"
#include "SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());

	if (SlashCharacter)
	{
		SlashCharterMovementComponent = SlashCharacter->GetCharacterMovement();
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (SlashCharterMovementComponent)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(SlashCharterMovementComponent->Velocity);

		IsFalling = SlashCharterMovementComponent->IsFalling();
	}
}
