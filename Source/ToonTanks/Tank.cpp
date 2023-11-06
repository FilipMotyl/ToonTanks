#include "Tank.h"
#include <Camera/CameraComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);

}
void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerPtr = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerPtr)
	{
		FHitResult hit;
		PlayerControllerPtr->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hit);
		RotateTurret(hit.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &ATank::Fire);
}

APlayerController* ATank::GetPlayerController() const
{
	return PlayerControllerPtr;
}

void ATank::Move(float Value)
{
	FVector MovementVector = FVector::ForwardVector * Value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddActorLocalOffset(MovementVector, true);
}

void ATank::Turn(float Value)
{
	FRotator Rotator = FRotator::ZeroRotator;
	Rotator.Yaw = Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddActorLocalRotation(Rotator, true);
}

