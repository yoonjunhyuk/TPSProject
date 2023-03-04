#include "Bullet.h"
#include <Components/SphereComponent.h>
#include <GameFramework/ProjectileMovementComponent.h>

// Sets default values dan
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// 1. �浹ü ���
	collisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComp"));
	// 2. �浹�������� ����
	collisionComp->SetCollisionProfileName(TEXT("BlockAll"));
	// 3. �浹ü ũ�� ����
	collisionComp->SetSphereRadius(13);
	// 4. ��Ʈ�� ���
	RootComponent = collisionComp;
	// 5. �ܰ� ������Ʈ ���
	bodyMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMeshComp"));
	// 6. �θ� ������Ʈ ����
	bodyMeshComp->SetupAttachment(collisionComp);
	// 7. �浹 ��Ȱ��ȭ
	bodyMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	// 8. �ܰ� ũ�� ����
	bodyMeshComp->SetRelativeScale3D(FVector(0.25f));

	// �߻�ü ������Ʈ
	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	// movement ������Ʈ�� ���Ž�ų ������Ʈ ����
	movementComp->SetUpdatedComponent(collisionComp);

	movementComp->InitialSpeed = 5000;
	movementComp->MaxSpeed = 5000;
	movementComp->bShouldBounce = true;
	movementComp->Bounciness = 0.3f;

	// ���� �ð� �ֱ�
	//InitialLifeSpan = 2.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle deathTimer;
	//GetWorld()->GetTimerManager().SetTimer(deathTimer, this, &ABullet::Die, 2.0f, false);

	GetWorld()->GetTimerManager().SetTimer(deathTimer, FTimerDelegate::CreateLambda([this]()->void
																					{
																						Destroy();
																					}), 2.0f, false);
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::Die()
{
	Destroy();
}
