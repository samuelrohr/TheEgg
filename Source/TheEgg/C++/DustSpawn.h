// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseActor.h"
#include "GameFramework/Actor.h"
#include "DustSpawn.generated.h"


UCLASS()
class THEEGG_API ADustSpawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADustSpawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Box que demarca a area possivel de se fazer spawn
	UPROPERTY(VisibleInstanceOnly, Category = Spawning)
		UCapsuleComponent *whereToSpawn;

	//Valor minimo para a scale do objeto a ser instanciado
	UPROPERTY(EditAnywhere, Category = Spawning)
		float objSpawnScaleMinRand = 1.0;

	//Valor maximo para a scale do objeto a ser instanciado
	UPROPERTY(EditAnywhere, Category = Spawning)
		float objSpawnScaleMaxRand = 1.0;

	//Objecto q spawn. Temos que usar uma TSubClassOf pois queremos que o usuário possa passar 
	//qualquer objeto baseado em um BasePickup, por exemplo um blueprint que herde da BasePickup
	UPROPERTY(EditAnywhere, Category = Spawning)
		TSubclassOf<class ABaseActor> whatToSpawn;

	//Minimo tempo de delay de spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float spawnDelayRangeLow;

	//Maximo tempo de delay de spawn
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spawning)
		float spawnDelayRangeHigh;

	//Função que retorna o ponto onde será instanciado o objeto
	UFUNCTION(BlueprintPure, Category = Spawning)
		FVector GetRandomPointInVolume();

	//Instancia o objeto no ponto indicado
	UFUNCTION(BlueprintCallable, Category = Spawning)
	void SpawnPickup();

private:

	//Tempo de delay
	float GetRandomSpawnDelay();
	
	//Delay atual
	float spawnDelay;

	//tempo para que seja feito o spawn
	float spawnTime;
	
};
