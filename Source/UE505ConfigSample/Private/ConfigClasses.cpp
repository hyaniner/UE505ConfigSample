// Fill out your copyright notice in the Description page of Project Settings.


#include "UE505ConfigSample/Public/ConfigClasses.h"

#include "ConfigTestSubsystem.h"

UE_DISABLE_OPTIMIZATION


UMyCustomFileNameBravoOne::UMyCustomFileNameBravoOne()
{
	UE_LOG(LogTemp, Warning, TEXT("생성자!"));
}

UMyCustomFileNameBravoTwo::UMyCustomFileNameBravoTwo()
{
	UE_LOG(LogTemp, Warning, TEXT("생성자!"));
}


UE_ENABLE_OPTIMIZATION



