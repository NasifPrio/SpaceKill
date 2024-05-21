// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceKill/SpaceKillCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SpaceKillGameModeBase.h"

// Sets default values
ASpaceKillCharacter::ASpaceKillCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpaceKillCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);

}

bool ASpaceKillCharacter::IsDead() const
{
	return Health <= 0;
}

float ASpaceKillCharacter::GetHealthPercentage() const
{
	return Health / MaxHealth;
}

// Called every frame  
void ASpaceKillCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASpaceKillCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &ASpaceKillCharacter::Shoot);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this , &ASpaceKillCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ASpaceKillCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &ASpaceKillCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASpaceKillCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &ASpaceKillCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &ASpaceKillCharacter::LookRightRate);

}

float ASpaceKillCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("Health left %f"), Health);

	if (IsDead())
	{
		ASpaceKillGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASpaceKillGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}

		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
	}

	return DamageToApply;

}

void ASpaceKillCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void ASpaceKillCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ASpaceKillCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void ASpaceKillCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void ASpaceKillCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ASpaceKillCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void ASpaceKillCharacter::Shoot()
{
	Gun->PullTrigger();
}




