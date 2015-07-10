// Fill out your copyright notice in the Description page of Project Settings.

#include "TheEgg.h"
#include "BaseActor.h"


// Sets default values
ABaseActor::ABaseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//BaseCollisionComponent server para lidar com as colisoes e por isso é invisivel 
	baseCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("rootComponent"));
	RootComponent = baseCollisionComponent;

	//Representacao visual do pickup
	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("baseMesh"));
	//Ligamos a fisica para esse elemento
	baseMesh->SetSimulatePhysics(true);

	//Colocamos a mesh como filha do componente base
	baseMesh->AttachTo(baseCollisionComponent);
}

// Called when the game starts or when spawned
void ABaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// ========= Custom Functions =========
void ABaseActor::OnPickedUp()
{
	//Implementacoes diferentes nas classes que herdarem essa
	//Destroy the batery
	Destroy();
}

void ABaseActor::SetMeshScale(FVector scale)
{
	baseMesh->SetRelativeScale3D(scale);
}