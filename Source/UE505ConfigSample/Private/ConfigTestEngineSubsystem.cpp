// Fill out your copyright notice in the Description page of Project Settings.


#include "UE505ConfigSample/Public/ConfigTestEngineSubsystem.h"

#include "UE505ConfigSample/Public/UE505ConfigSample.h"


void UConfigTestEngineSubsystem::PostInitProperties()
{
	Super::PostInitProperties();

	if (!IsTemplate())
	{
		UE_LOG(CTestLog, Warning, TEXT("서브시스템 시작"))	
	}
}
