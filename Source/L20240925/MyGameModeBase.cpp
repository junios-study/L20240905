// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Engine.h"

AMyGameModeBase::AMyGameModeBase()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello World2"));
	//check(false);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, TEXT("Hello World"));
	}
}
