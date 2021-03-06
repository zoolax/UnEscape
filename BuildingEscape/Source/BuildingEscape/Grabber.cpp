// Zoolax inc 2017 copy right

#include "Grabber.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/InputComponent.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"
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
	// ...
	FindPhysicsComponent();
	SetupInputComponent();
	
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass <UInputComponent>();
	//---------
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabObject);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseObject);
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//UE_LOG(LogTemp,Warning,TEXT(" location %s , rotation %s"), *PlayerViewPointLocation.ToString(), *PlayerViewRotation.ToString())
	DrawDebugLine(GetWorld(),
		GetReachStartLine(),
		GetReachEndLine(),
		FColor(255, 0, 0),
		false,
		0,
		0,
		12.f);
	//--------
	//setup params query
	FCollisionQueryParams TracePar(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(OUT Hit,
		GetReachStartLine(),
		GetReachEndLine(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TracePar
	);

	if (Hit.Actor != nullptr)
	{
		FString _name = Hit.Actor->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Object got hit: %s"), *_name);
	}
	//--------
	return Hit;
}


void UGrabber::FindPhysicsComponent()
{
	/// Look for physicc handler
	PhysicsHandle = GetOwner()->FindComponentByClass  <UPhysicsHandleComponent>();
	//---------
	if (PhysicsHandle)
	{
		//physics handle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The name of object missing handle componnet"), *GetOwner()->GetName());
	}
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//--------
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//--------
	// ...
	if (!PhysicsHandle)
		return;

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetReachEndLine());
	}

}

FVector UGrabber::GetReachEndLine()
{
	//Get the player view point this thick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewRotation
	);
	return  PlayerViewPointLocation + PlayerViewRotation.Vector() *  60.f;
}

FVector UGrabber::GetReachStartLine()
{
	//Get the player view point this thick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewRotation
	);

	return PlayerViewPointLocation;
}


void UGrabber::GrabObject()
{
	//Line trace here
	auto HitRes = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitRes.GetComponent();
	auto ActorHit = HitRes.GetActor();

	if (ActorHit)
	{
		PhysicsHandle->GrabComponent(ComponentToGrab,NAME_None,ComponentToGrab->GetOwner()->GetActorLocation(),true);
	}


}

void UGrabber::ReleaseObject()
{
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->ReleaseComponent();
	}
}