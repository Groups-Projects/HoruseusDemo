// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MyCharacter.h"
#include "HoruseusDemoGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	portalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Portal Mesh"));
	//Set Default Values for the components.
	SetRootComponent(portalMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
	CollisionBox->SetCollisionProfileName("Trigger");
	CollisionBox->SetupAttachment(portalMesh);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	GameModeRef = Cast<AHoruseusDemoGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AMyCharacter::StaticClass()))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "enter portal");
		GameModeRef->OpenBossLevel();
	}
}

