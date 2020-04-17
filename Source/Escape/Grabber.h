// Copyright Michael Brisson 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UGrabber();

private:
	// Distance player can reach out to grab
	UPROPERTY(EditAnywhere)
		float Reach = 100.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* Input;
	bool bIsHolding = false;

	void Grab();
	void GetPhysicsHandle();
	void GetInput();

	// Return first actor within reach having a physics body
	FHitResult GetFirstObjectInReach() const;
	FVector GetRaycastEnd() const;
	FVector GetPlayersPosition() const;
};
