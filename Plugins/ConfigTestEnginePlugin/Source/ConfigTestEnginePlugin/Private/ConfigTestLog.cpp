// Fill out your copyright notice in the Description page of Project Settings.


#include "ConfigTestLog.h"


UE_DISABLE_OPTIMIZATION

UConfigTestLog* UConfigTestLog::Get()
{
	if (GWorld)
	{
		const UGameInstance* GameInstance = GWorld->GetGameInstance();
		return GameInstance->GetSubsystem<UConfigTestLog>();
	}

	return nullptr;	
}

UE_ENABLE_OPTIMIZATION








