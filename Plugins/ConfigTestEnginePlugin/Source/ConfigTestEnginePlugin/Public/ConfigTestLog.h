// https://github.com/hyaniner/UE505ConfigSample

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConfigTestLog.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateLog, FString, MessageString);

/**
 * 
 * 
 * Subsystems are some kinds of singleton classes of Unreal Engine. They are useful when you need to access something globally.
 * https://dev.epicgames.com/documentation/en-us/unreal-engine/programming-subsystems-in-unreal-engine
 */
UCLASS(Blueprintable, BlueprintType)
class CONFIGTESTENGINEPLUGIN_API UConfigTestLog : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:

	static UConfigTestLog* Get();	

	/*
	 * This is the text displayed in the MultiLineEditableTextBox.
	 * By this approach, we can handle cases where console or debugging messages are not available,
	 * such as a packaged build.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "ConfigSampleAPI")
	FString DisplayedLog;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "USAPI|GameBoard", meta = (CallInEditor = "true"))
	FOnUpdateLog OnUpdateLog;
	
};


