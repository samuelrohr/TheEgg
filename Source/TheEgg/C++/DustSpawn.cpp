// Fill out your copyright notice in the Description page of Project Settings.

#include "TheEgg.h"
#include "DustSpawn.h"


// Sets default values
ADustSpawn::ADustSpawn()
{
	//Criamos a caixa q delimita a area onde podem ser instanciados poickups
	whereToSpawn = CreateDefaultSubobject<UCapsuleComponent>(TEXT("whereToSpawn"));
	RootComponent = whereToSpawn;

	spawnDelayRangeLow = 1.0f;
	spawnDelayRangeHigh = 4.5f;
	spawnDelay = GetRandomSpawnDelay();

	//Vamos usar a tick function para instanciar
	//para isso precisamos ativar o tick para essa classe
	//PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADustSpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADustSpawn::Tick( float DeltaTime )
{
	Super::Tick(DeltaTime);

	spawnTime += DeltaTime;

	if (spawnTime > spawnDelay)
	{
		SpawnPickup();

		//zeramos o spawntime e sorteamos um novo delay
		spawnTime -= spawnDelay;
		spawnDelay = GetRandomSpawnDelay();
	}
}

float ADustSpawn::GetRandomSpawnDelay()
{
	return FMath::FRandRange(spawnDelayRangeLow, spawnDelayRangeHigh);
}

void ADustSpawn::SpawnPickup()
{
	//Verifica se tem um objeto para instanciar
	if (whatToSpawn != NULL)
	{
		//Verifica se tem um mundo valido
		UWorld* const world = GetWorld();
		if (world)
		{
			//Parametros para spawn
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;

			//Local de spawn
			FVector spawnLocation = GetRandomPointInVolume();

			//Rotação ao spawn
			FRotator spawnRotation;
			spawnRotation.Yaw = FMath::FRand() * 360.f;
			spawnRotation.Pitch = FMath::FRand() * 360.f;
			spawnRotation.Roll = FMath::FRand() * 360.f;

			//Setamos a scale do objeto
			float scale = FMath::FRandRange(objSpawnScaleMinRand, objSpawnScaleMaxRand);
			FVector objSpawnScale = FVector(scale, scale, scale);
			whatToSpawn->GetDefaultObject<ABaseActor>()->SetMeshScale(objSpawnScale);

			//Spawn do item.
			ABaseActor* const spawnedPickup = world->SpawnActor<ABaseActor>(whatToSpawn, spawnLocation, spawnRotation, spawnParams);
		}
	}
}

FVector ADustSpawn::GetRandomPointInVolume()
{
	FVector randomLocation;
	//float minX, minY, minZ;
	//float maxX, maxY, maxZ;
	float minZ, maxZ;
	float randX, randY, randZ;
	float radius = 0;

	FVector origin;
	float capsuleHalfHeight;
	float capsuleRadius;


	//Origem e extensao da caixa q demarca onde instanciar o objeto
	origin = whereToSpawn->Bounds.Origin;
	//Esse valor é do topo até o meio do cilindro
	capsuleHalfHeight = whereToSpawn->GetScaledCapsuleHalfHeight();
	capsuleRadius = whereToSpawn->GetScaledCapsuleRadius();

	//Convertemos somente para a altura do cilindro
	capsuleHalfHeight = capsuleHalfHeight - capsuleRadius;

	radius = capsuleRadius;

	minZ = origin.Z - capsuleHalfHeight - capsuleRadius;
	maxZ = origin.Z + capsuleHalfHeight + capsuleRadius;

	randZ = FMath::FRandRange(minZ, maxZ);

	//Se o valor (absoluto) sorteado foi maior que o HalfHeight estamos na regiao
	//esperica assim precisamos achar o novo raio
	if (randZ > (origin.Z + capsuleHalfHeight))
	{
		UE_LOG(LogTemp, Warning, TEXT("randZ %f"), randZ);
		//Na esfera o raio irá aumentar ou diminuir de acorodo com o Z
		//Achamos o novo raio fazendo regra de triangulos dentro da esfera
		float zInside = FMath::Abs(randZ) - (origin.Z + capsuleHalfHeight);
		UE_LOG(LogTemp, Warning, TEXT("zinside %f"), zInside);
		radius = FMath::Sqrt((capsuleRadius * capsuleRadius) - (zInside * zInside));
		UE_LOG(LogTemp, Warning, TEXT("newradius %f"), radius);
	}
	else if (randZ < (origin.Z - capsuleHalfHeight))
	{
		UE_LOG(LogTemp, Warning, TEXT("randZ %f"), randZ);
		float zInside = (origin.Z - capsuleHalfHeight) - randZ;
		UE_LOG(LogTemp, Warning, TEXT("zinside %f"), zInside);
		radius = FMath::Sqrt((capsuleRadius * capsuleRadius) - (zInside * zInside));
		UE_LOG(LogTemp, Warning, TEXT("newradius %f"), radius);
	}
	//Se não, basta tratar como um cilindro. Usando o raio ja conhecido

	//Sorteamos um angulo
	float randAngle = FMath::FRandRange(0, 360);

	//Encontramos o X e Y
	randX = origin.X + (radius * FMath::Cos(randAngle));
	randY = origin.Y + (radius * FMath::Sin(randAngle));

	randomLocation.X = randX;
	randomLocation.Y = randY;
	randomLocation.Z = randZ;

	return randomLocation;
}
