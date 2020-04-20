// Copyright Michael Brisson 2020

#include "Grabber.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"
#include "Engine\World.h"
#include "GameFramework\PlayerController.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	GetPhysicsHandle();
	GetInput();
}

FVector UGrabber::GetRaycastEnd() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

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
	return RaycastEnd;
}

void UGrabber::Grab()
{
	bIsHolding = !bIsHolding;
	if (bIsHolding)
	{
		UE_LOG(LogTemp, Warning, TEXT("Button Pressed"));
		FHitResult HitResult = GetFirstObjectInReach();
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
		AActor* ActorHit = HitResult.GetActor();

		if (ActorHit)
		{
			if(!PhysicsHandle) {return;}

			/*PhysicsHandle->GrabComponentAtLocation
			(
				ComponentToGrab,
				NAME_None,
				GetRaycastEnd()
			);*/

			PhysicsHandle->GrabComponent
			(
				ComponentToGrab,
				NAME_None,
				GetRaycastEnd(),
				true
			);
		}
	}
	else
	{
		if (!PhysicsHandle) { return; }

		UE_LOG(LogTemp, Warning, TEXT("Button RELEASED"));
		PhysicsHandle->ReleaseComponent();
	}
}

void UGrabber::GetPhysicsHandle()
{
	//Check for physics handle component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing PhysicsHandle Component"), *GetOwner()->GetName());
	}
}

void UGrabber::GetInput()
{
	Input = GetOwner()->FindComponentByClass<UInputComponent>();
	if (Input)
	{
		Input->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
}

FHitResult UGrabber::GetFirstObjectInReach() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	//GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	//FVector RaycastEnd = PlayerViewpointLocation + PlayerViewpointRotation.Vector() * Reach;

	//DrawDebugLine(
	//	GetWorld(),
	//	PlayerViewpointLocation,
	//	RaycastEnd,
	//	FColor().Green,
	//	false,
	//	0.f,
	//	0,
	//	5.f
	//);

	// Raycast
	FHitResult Hit;
	FCollisionQueryParams TraceParams(GetFName(), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetPlayersPosition(),
		GetRaycastEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();

	if (Hit.Actor != NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *ActorHit->GetName());
	}
	return Hit;
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the PhysicsHandle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// Move object being held
		PhysicsHandle->SetTargetLocation(GetRaycastEnd());
	}

}

FVector UGrabber::GetPlayersPosition() const
{
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);

	return PlayerViewpointLocation;
}

