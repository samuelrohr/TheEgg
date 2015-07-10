// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseActor.generated.h"

UCLASS()
class THEEGG_API ABaseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseActor();

	//Root component, invisivel
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UBoxComponent* baseCollisionComponent;

	//Mesh do pickup
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		UStaticMeshComponent* baseMesh;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//Permite o usuário setar a scale do objeto.
	void SetMeshScale(FVector scale);

	UFUNCTION(BlueprintCallable, Category = Functions)
		void OnPickedUp();
	
};
