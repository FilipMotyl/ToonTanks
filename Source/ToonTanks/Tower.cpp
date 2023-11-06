#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	GetWorldTimerManager().SetTimer(FireCooldownTimerHandle, this, &ATower::CheckFireCondition, FireCooldown, true);
}

void ATower::CheckFireCondition()
{
	if (!Tank)
		return;

	if (InFireRange() && Tank->bAlive)
		Fire();
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		return (FVector::DistSquared(GetActorLocation(), Tank->GetActorLocation()) <= Range * Range);
	}
	UE_LOG(LogTemp, Display, TEXT("Tank pointer null error"));
	return false;
}