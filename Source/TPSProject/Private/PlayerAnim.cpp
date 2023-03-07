#include "PlayerAnim.h"
#include "TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// 소유 폰 얻어 오기
	auto ownerPawn = TryGetPawnOwner();
	// 플레이어로 캐스팅하기
	auto player = Cast<ATPSPlayer>(ownerPawn);

	if (player)
	{
		// 이동 속도 받아오기
		FVector velocity = player->GetVelocity();
		// 플레이어의 전방 벡터 받아오기
		FVector forwardVector = player->GetActorForwardVector();
		// speed에 값(내적) 할당하기
		speed = FVector::DotProduct(forwardVector, velocity);
		// 좌우 속도 할당하기
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);

		// 플레이어가 현재 공중에 있는지 여부를 기억하기
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}

void UPlayerAnim::PlayAttackAnim()
{
	Montage_Play(attackAnimMontage);
}