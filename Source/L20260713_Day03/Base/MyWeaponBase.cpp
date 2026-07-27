// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ProjectileBase.h"

// Sets default values
AMyWeaponBase::AMyWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void AMyWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CoolDown = FMath::Max(CoolDown - DeltaTime, 0);

	if (bCanFire)
	{
		if (CoolDown <= 0.f)
		{
			Fire();
			MakeMuzzleFlash();
			CoolDown = FiringRate;
			//UE_LOG(LogTemp, Warning, TEXT("Fire"));
		}
	}

}


void AMyWeaponBase::StartFire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Start Fire"));

	bCanFire = true;
	FiringRate = FireRate;
}


void AMyWeaponBase::StopFire()
{
	//UE_LOG(LogTemp, Warning, TEXT("Stop Fire"));

	bCanFire = false;
}

void AMyWeaponBase::Fire()
{
	FHitResult OutResult;
	
	if (LineTrace(OutResult))
	{

	}
	else
	{

	}

}

void AMyWeaponBase::MakeMuzzleFlash()
{
	UGameplayStatics::SpawnEmitterAtLocation(
		GetWorld(),
		MuzzleFlash,
		Mesh->GetSocketLocation(TEXT("MuzzleFlash"))
	);
}

bool AMyWeaponBase::LineTrace(FHitResult& OutResult)
{
	bool bResult = false;

	AMyCharacter* Pawn = Cast<AMyCharacter>(GetOwner());
	if (!Pawn)
	{
		return bResult;
	}

	APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
	if (!PC)
	{
		return bResult;
	}

	int ScreenSizeX = 0;
	int ScreenSizeY = 0;
	int CenterX = 0;
	int CenterY = 0;
	float Range = 99999.f;

	FVector WorldLocation;
	FVector WorldDirection;

	PC->GetViewportSize(ScreenSizeX, ScreenSizeY);

	CenterX = ScreenSizeX / 2;
	CenterY = ScreenSizeY / 2;

	//2D -> 3D
	PC->DeprojectScreenPositionToWorld(CenterX,
		CenterY,
		WorldLocation,
		WorldDirection
	);


	//FVector Start = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation();
	//WorldDirection = UKismetMathLibrary::GetForwardVector(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraRotation());
	FVector Start = Pawn->Camera->GetComponentLocation();
	FVector End = Start + (WorldDirection * Range);

	TArray<AActor*> IgnoreActors;



	//Camera LineTrace
	bResult = UKismetSystemLibrary::LineTraceSingle(GetWorld(),
		Start,
		End,
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		true,
		IgnoreActors,
		EDrawDebugTrace::None,
		OutResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		3.0f
	);


	Start = Mesh->GetSocketLocation(TEXT("Muzzle"));
	FVector ForwardVector = OutResult.ImpactPoint - Start;
	ForwardVector.Normalize();
	End = Start + (ForwardVector * Range);

	End = OutResult.bBlockingHit ? End : OutResult.TraceEnd;

	FRotator SpawnRotator = UKismetMathLibrary::FindLookAtRotation(
		Start, End
	);

	GetWorld()->SpawnActor<AProjectileBase>(ProjectileTemplate,
		Start,
		SpawnRotator
	);





	return bResult;
}
