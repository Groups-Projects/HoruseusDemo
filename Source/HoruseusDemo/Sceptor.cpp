// Fill out your copyright notice in the Description page of Project Settings.


#include "Sceptor.h"
#include "MyCharacter.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASceptor::ASceptor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	SetRootComponent(WeaponMesh);



}

// Called when the game starts or when spawned
void ASceptor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASceptor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

