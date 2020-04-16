// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework\Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString Log = FString::Printf(TEXT("Hello"));
	FString* PrintLog = &Log;

	FString ActorName;
	ActorName = GetOwner()->GetName();

	FString ActorLocation;
	ActorLocation = GetOwner()->GetActorLocation().ToString();

	FString* AName = &ActorName;
	FString* ALocation = &ActorLocation;


	//UE_LOG(LogTemp, Warning, TEXT("The object \"%s\" is located at %s"), **AName, **ALocation);
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

