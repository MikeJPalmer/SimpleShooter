// Copyright 2020 Michael Palmer & Paradigm Game Studios


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());

	if (OwnerPawn == nullptr) { return; }

	AController* OwnerController = OwnerPawn->GetController();

	if (OwnerController == nullptr) { return; }

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;

	FHitResult Hit;

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);

	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();

		// DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);

		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShotImpact, Hit.Location, ShotDirection.Rotation());

		AActor* HitActor = Hit.GetActor();

		if (HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90.f, 2.f, FColor::Red, true);
}