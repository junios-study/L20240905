// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>("Box");
	RootComponent = Box;

	Body = CreateDefaultSubobject<UStaticMeshComponent>("Body");
	Body->SetupAttachment(RootComponent);
	Body->AddRelativeRotation(FRotator(-90.f, 0, 0));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Script/Engine.StaticMesh'/Game/P38/Meshes/SM_Rocket.SM_Rocket'"));
	if (SM_Body.Succeeded())
	{
		Body->SetStaticMesh(SM_Body.Object);
	}


	Movement = CreateDefaultSubobject<UProjectileMovementComponent>("Movement");
	Movement->InitialSpeed = 3000.0f;
	Movement->ProjectileGravityScale = 0.0f;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.0f);

	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessOverlap);
	//OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessOverlap);
	//OnActorBeginOverlap.RemoveAll(this);

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyActor::ProcessOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap Actor : %s"), *OtherActor->GetName());
	//다른 처리 그건 아트, 기획자 제공
	//MakeBPCallCPP(10);
	MakeBPToNativeCallCPP(20);
}

void AMyActor::MakeCPPCallBP(int32 Number)
{

	UE_LOG(LogTemp, Warning, TEXT("이건 BP에서 호출한 CPP 함수 %d"), Number);
}

void AMyActor::MakeBPToNativeCallCPP_Implementation(int32 Number)
{
	UE_LOG(LogTemp, Warning, TEXT("이건 BP에서 호출한 CPP 함수 Native %d"), Number);

}

