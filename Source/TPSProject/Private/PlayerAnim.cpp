#include "PlayerAnim.h"
#include "TPSPlayer.h"
#include <GameFramework/CharacterMovementComponent.h>

void UPlayerAnim::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// ���� �� ��� ����
	auto ownerPawn = TryGetPawnOwner();
	// �÷��̾�� ĳ�����ϱ�
	auto player = Cast<ATPSPlayer>(ownerPawn);

	if (player)
	{
		// �̵� �ӵ� �޾ƿ���
		FVector velocity = player->GetVelocity();
		// �÷��̾��� ���� ���� �޾ƿ���
		FVector forwardVector = player->GetActorForwardVector();
		// speed�� ��(����) �Ҵ��ϱ�
		speed = FVector::DotProduct(forwardVector, velocity);
		// �¿� �ӵ� �Ҵ��ϱ�
		FVector rightVector = player->GetActorRightVector();
		direction = FVector::DotProduct(rightVector, velocity);

		// �÷��̾ ���� ���߿� �ִ��� ���θ� ����ϱ�
		auto movement = player->GetCharacterMovement();
		isInAir = movement->IsFalling();
	}
}

void UPlayerAnim::PlayAttackAnim()
{
	Montage_Play(attackAnimMontage);
}