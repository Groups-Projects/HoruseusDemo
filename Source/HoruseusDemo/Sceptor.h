// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sceptor.generated.h"

class USkeletalMeshComponent;

UCLASS()
class HORUSEUSDEMO_API ASceptor : public AActor
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    ASceptor();

    class AMyCharacter* character;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
        class UBoxComponent* CollisionBox;

    UPROPERTY(EditAnywhere)
        bool canAttack;

    UFUNCTION()
        void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
        void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
    UPROPERTY(EditAnywhere)
        USkeletalMeshComponent* weaponMesh;


};
