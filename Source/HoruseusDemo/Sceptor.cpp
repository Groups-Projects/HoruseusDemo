// Fill out your copyright notice in the Description page of Project Settings.


#include "Sceptor.h"
#include "MyCharacter.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "EnemyAIController.h"

// Sets default values
ASceptor::ASceptor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    character = Cast<AMyCharacter>(GetOwner());

    weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon"));

    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
    CollisionBox->SetBoxExtent(FVector(32.0f, 32.0f, 32.0f));
    CollisionBox->SetCollisionProfileName("Trigger");
    CollisionBox->SetupAttachment(weaponMesh);

    CanAttack = false;
}

// Called when the game starts or when spawned
void ASceptor::BeginPlay()
{
	Super::BeginPlay();
   
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ASceptor::OnOverlapBegin);
    //CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ASceptor::OnOverlapEnd);
}

// Called every frame
void ASceptor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASceptor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (CanAttack)
    {
        AActor* owner = this->GetOwner();
        if (owner)
        {
            if ((owner->ActorHasTag("Enemy") && OtherActor->ActorHasTag("Player")) || owner->ActorHasTag("Player") && OtherActor->ActorHasTag("Enemy"))
            {
                //GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, "HITTING");
                UGameplayStatics::ApplyDamage(OtherActor, 10.0f, owner->GetInstigatorController(), this, UDamageType::StaticClass());
                CanAttack = false;
            }
        }
    }
}

void ASceptor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
   
}

