// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sceptor.generated.h"

class UStaticMeshComponent;

UCLASS()
class HORUSEUSDEMO_API ASceptor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASceptor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* WeaponMesh;

	/*
	UFUNCTION()
		void OnOverlapBegin(
			AActor* OverlappedActor, // this
			AActor* OtherActor
		);

	UFUNCTION()
		void OnOverlapEnd(
			AActor* OverlappedActor, // this
			AActor* OtherActor
		);

	*/


};
