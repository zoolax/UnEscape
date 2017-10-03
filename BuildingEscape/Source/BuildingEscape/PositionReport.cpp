// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UPositionReport::RotateObject()
{

	if (CurOwnerActor != nullptr)
	{
		FRotator _rotator = CurOwnerActor->GetActorRotation();

		_rotator = FRotator(_rotator.Pitch , _rotator.Yaw + RotationSpeed, _rotator.Roll );
		CurOwnerActor->SetActorRotation(_rotator);
	}

}

// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// ...


	CurOwnerActor = GetOwner();

	FString _name = CurOwnerActor->GetName();
	FVector VectorPos = CurOwnerActor->GetActorLocation();
	FString ObjectPos = CurOwnerActor->GetTransform().GetLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *_name,*ObjectPos);
	
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//-------
	// ...
	PrintLocations();
	//RotateObject();
	//-------
}

void UPositionReport::PrintLocations()
{
	FrameNum++;
	if (FrameNum % 60 == 0)
	{
		FVector _vec3 = GetOwner()->GetActorLocation();
		UE_LOG(LogTemp, Warning, TEXT("Position reporter reporting %s %d"), *_vec3.ToString()+ FrameNum);
	}

}




