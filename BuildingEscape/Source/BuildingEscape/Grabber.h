// Zoolax inc 2017 copy right

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;



	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	
	UPhysicsHandleComponent*  PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
		
	void GrabObject();
	void ReleaseObject();
	void FindPhysicsComponent();
	void SetupInputComponent();

	const FHitResult GetFirstPhysicsBodyInReach();
	
};
