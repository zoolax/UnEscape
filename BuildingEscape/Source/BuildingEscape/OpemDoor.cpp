// Zoolax inc 2017 copy right

#include "OpemDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UOpemDoor::UOpemDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpemDoor::BeginPlay()
{
	Super::BeginPlay();

	// ...
	ActorThatOpens = GetWorld()-> GetFirstPlayerController()-> GetPawn();
	 
	
}

void UOpemDoor::OpenDoor()
{
	AActor* Owner = GetOwner();

	FRotator NewRotation = FRotator(0.0f, -110.0f, 0.0f);

	Owner->SetActorRotation(NewRotation);

	FTransform Trans = Owner->GetTransform();
	FQuat Rotation = Trans.GetRotation();
}

void UOpemDoor::CloseDoor()
{
	AActor* Owner = GetOwner();

	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));

	FTransform Trans = Owner->GetTransform();
	FQuat Rotation = Trans.GetRotation();
}


// Called every frame
void UOpemDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();

	}

	//check if it is time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > 0.56f)
	{
		CloseDoor();
	}
}
