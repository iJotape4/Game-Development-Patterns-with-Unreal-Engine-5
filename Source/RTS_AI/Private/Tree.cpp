// Fill out your copyright notice in the Description page of Project Settings.


#include "Tree.h"

#include "Kismet/KismetSystemLibrary.h"

// Sets default values
ATree::ATree()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATree::BeginPlay()
{
	Super::BeginPlay();

}

void ATree::Ignite_Implementation()
{
	IFlammable::Ignite_Implementation();
}

// Called every frame
void ATree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Interface Usage

void ATree::OnSphereOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool FromSweep, const FHitResult& SweepResult)
{
	if (UKismetSystemLibrary::DoesImplementInterface(OtherActor, UFlammable::StaticClass()))
	{
		IFlammable::Execute_Ignite(OtherActor);
	}

}