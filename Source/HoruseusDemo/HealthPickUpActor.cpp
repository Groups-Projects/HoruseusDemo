// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUpActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "MyCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AHealthPickUpActor::AHealthPickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthPickMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Health Pick Mesh"));
	HealthPickMesh->SetupAttachment(RootComponent);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetupAttachment(HealthPickMesh);

}



// Called when the game starts or when spawned
void AHealthPickUpActor::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AHealthPickUpActor::OnOverlapBegin);
	
}

// Called every frame
void AHealthPickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHealthPickUpActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		//If the other Actor class is a AMainCharacter and has player tag.
		if (OtherActor->GetClass()->IsChildOf(AMyCharacter::StaticClass()) && OtherActor->ActorHasTag("Player"))
		{
			if (Cast<AMyCharacter>(OtherActor)->health >= 100)
			{
				UE_LOG(LogTemp, Warning, TEXT("Health is full and player can't heal."));
			}
			else
			{
				Cast<AMyCharacter>(OtherActor)->HealthPickup();
				Destroy();
			}
		}
	}
}
