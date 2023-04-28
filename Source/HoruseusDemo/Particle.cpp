// Fill out your copyright notice in the Description page of Project Settings.


#include "Particle.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AParticle::AParticle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates subobjects for the different components in the editor.
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));

	//Set Default Values for the components.
	SetRootComponent(Root);
	Particle->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AParticle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AParticle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

