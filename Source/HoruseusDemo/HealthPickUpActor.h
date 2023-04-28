// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HealthPickUpActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AMyCharacter;


UCLASS()
class HORUSEUSDEMO_API AHealthPickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealthPickUpActor();

	AMyCharacter* myCharacter;


	UPROPERTY(VisibleAnywhere)
		UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* HealthPickMesh;
	
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
