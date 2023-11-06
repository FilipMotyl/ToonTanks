#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	ABasePawn();

protected:
	virtual void BeginPlay() override;

	void RotateTurret(FVector Target);

	void Fire();

public:	
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

private: 
	UPROPERTY(EditAnywhere, Category = "Base Components")
	float TurretRotationSpeed = 15;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Base Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "Base Components")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Base Componenets")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditAnywhere, Category = "Base Components")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Base Components")
	TSubclassOf<UCameraShakeBase> DeathCamerShakeClass;
};
