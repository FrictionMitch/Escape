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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void GetSound();
	float GetTotalMassOfActors() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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
		float DoorCloseDelay = 2.f;
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
		AActor* ObjectThatOpensDoor = nullptr;
	UPROPERTY(EditAnywhere)
		UAudioComponent* DoorOpenSound = nullptr;
	UPROPERTY(EditAnywhere)
		UAudioComponent* DoorCloseSound = nullptr;

	bool bIsDoorTriggerd = false;
	bool bOpenDoorHasPlayed = false;
	bool bCloseDoorHasPlayed = true;
	float InitialYaw;
	float CurrentYaw;
	float DoorLastOpened = 0.f;

};
