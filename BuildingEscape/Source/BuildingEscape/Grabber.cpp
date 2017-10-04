// Zoolax inc 2017 copy right

#include "Grabber.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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

	UE_LOG(LogTemp, Warning, TEXT("Grabber is here"));
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//--------
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//--------
	// ...
	//Get the player view point this thick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
	OUT PlayerViewPointLocation,
	OUT PlayerViewRotation
	);

	//UE_LOG(LogTemp,Warning,TEXT(" location %s , rotation %s"), *PlayerViewPointLocation.ToString(), *PlayerViewRotation.ToString())
	//--------
	//Ray-cast out to reach the distance
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewRotation.Vector() *  60.f;
	DrawDebugLine(GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0,
		0,
		12.f);
	//--------
	// See what we have hit
	//--------
}

