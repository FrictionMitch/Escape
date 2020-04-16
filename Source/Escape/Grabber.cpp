// Copyright Michael Brisson 2020

#include "CollisionQueryParams.h"
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

	//Check for physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	Input = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PhysicsHandle)
	{
		if (Input)
		{
			UE_LOG(LogTemp, Warning, TEXT("Input found"));
			Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing PhysicsHandle Component"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Button Pressed"));
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

	FVector RaycastEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerViewpointLocation,
		RaycastEnd,
		FColor().Green,
		false,
		0.f,
		0,
		5.f
	);

	// Raycast
	FHitResult Hit;
	FCollisionQueryParams TraceParams(GetFName(), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		RaycastEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();

	if (Hit.Actor != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHit->GetName());
	}
}

