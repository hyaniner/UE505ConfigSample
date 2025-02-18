// https://github.com/hyaniner/UE505ConfigSample


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








