// Copyright Michael Brisson 2020

#include "DrawDebugHelpers.h"
#include "Engine\World.h"
#include "Grabber.h"
#include "GameFramework\PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	//Get Player Viewpoint
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	//UE_LOG(LogTemp, Warning, TEXT("Viewpoint Location: %s\n Viewpoint Rotation: %s"), 
	//	*PlayerViewpointLocation.ToString(), 
	//	*PlayerViewpointRotation.ToString()
	//);

	FVector LineEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewpointLocation,
		LineEnd,
		FColor().Green,
		false,
		0.f,
		0,
		5.f
	);
}

