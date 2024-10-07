// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"

#include "MyActor.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("박스"));
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(Box);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Body.SM_P38_Body'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}

	Left = CreateDefaultSubobject<UStaticMeshComponent>("Left");
	Left->SetupAttachment(Body);

	Right = CreateDefaultSubobject<UStaticMeshComponent>("Right");
	Right->SetupAttachment(Body);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Propeller(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_P38_Propeller.SM_P38_Propeller'"));
	if (SM_Propeller.Succeeded())
	{
		Left->SetStaticMesh(SM_Propeller.Object);
		Right->SetStaticMesh(SM_Propeller.Object);
	}

	Left->SetRelativeLocation(FVector(37.019806f, 21.f, 1.04f));
	Right->SetRelativeLocation(FVector(37.019806f, -21.f, 1.04f));


	Arrow = CreateDefaultSubobject<UArrowComponent>("Arrow");
	Arrow->SetupAttachment(Box);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(Box);
	
	SpringArm->bEnableCameraLag = true;

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	Movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	Movement->MaxSpeed = 0;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();

	//for (TFieldIterator<UFunction> FuntionIT(GetClass()); FuntionIT; ++FuntionIT)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Name : %s"), *FuntionIT->GetName());

	//}

	//for (TFieldIterator<FProperty> PropIt(GetClass()); PropIt; ++PropIt)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Name : %s"), *PropIt->GetName());
	//	
	//}

}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostScale);
	//Left->AddLocalRotation(FRotator(0, 0, 3600 * DeltaTime));
	//Right->AddLocalRotation(FRotator(0, 0, 3600 * DeltaTime));
	RotatePropeller(Left);
	RotatePropeller(Right);
}

void AMyPawn::RotatePropeller(UStaticMeshComponent* Where)
{
	Where->AddLocalRotation(FRotator(0, 0, 3600 * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);
	PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed,  this, &AMyPawn::Fire);

	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Pressed,  this, &AMyPawn::Boost);
	PlayerInputComponent->BindAction(TEXT("Boost"), IE_Released,  this, &AMyPawn::StopBoost);
}

void AMyPawn::Roll(float Value)
{
	float Normalize = FMath::Clamp(Value, -1.f, 1.f);

	AddActorLocalRotation(FRotator(0, 0, 60 * Normalize * UGameplayStatics::GetWorldDeltaSeconds(GetWorld())));
}

void AMyPawn::Pitch(float Value)
{
	float Normalize = FMath::Clamp(Value, -1.f, 1.f);

	AddActorLocalRotation(FRotator(60 * Normalize * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0, 0));
}

void AMyPawn::Fire()
{
	AActor* NewActor = GetWorld()->SpawnActor<AActor>(RocketTemplate, Arrow->K2_GetComponentLocation(), Arrow->GetComponentRotation());
}

void AMyPawn::Boost()
{
	BoostScale = 1.0f;
}

void AMyPawn::StopBoost()
{
	BoostScale = 0.5f;
}

