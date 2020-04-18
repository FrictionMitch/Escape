// Copyright Michael Brisson 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	float GetTotalMassOfActors() const;

private:
	UPROPERTY(EditAnywhere)
		float RotationAmount = 90.f;
	UPROPERTY(EditAnywhere)
		float OpenSpeed = 0.5f;
	UPROPERTY(EditAnywhere)
		float CloseSpeed = 1.f;
	UPROPERTY(EditAnywhere)
		float DoorTriggerAmount = 60.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	UPROPERTY(EditAnywhere)
		AActor* ObjectThatOpensDoor;

	bool bIsDoorTriggerd = false;
	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 2.f;
};
