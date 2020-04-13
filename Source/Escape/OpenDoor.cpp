// Copyright Michael Brisson 2020


#include "OpenDoor.h"
#include "GameFramework\Actor.h"
#include "GameFramework\PlayerController.h"
#include "Engine\World.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	ObjectThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	RotationAmount += InitialYaw;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing the PRESSURE PLATE object"), *GetOwner()->GetName());
	}
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate)
	{
		if (PressurePlate->IsOverlappingActor(ObjectThatOpensDoor))
		{
			bIsDoorTriggerd = true;
		}
		else
		{
			bIsDoorTriggerd = false;
		}
		OpenDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	FRotator OpenRotation = GetOwner()->GetActorRotation();
	if (bIsDoorTriggerd)
	{
		CurrentYaw = FMath::Lerp(CurrentYaw, RotationAmount, RotationSpeed * DeltaTime);
	}
	else
	{
		CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, RotationSpeed * DeltaTime);
	}

	OpenRotation.Yaw = CurrentYaw;

	GetOwner()->SetActorRotation(OpenRotation);
}

