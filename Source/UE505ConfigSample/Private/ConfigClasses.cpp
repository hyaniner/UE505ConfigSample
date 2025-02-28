// https://github.com/hyaniner/UE505ConfigSample


#include "UE505ConfigSample/Public/ConfigClasses.h"

#include "ConfigTestSubsystem.h"

UE_DISABLE_OPTIMIZATION



UCustomInGameModuleBravoOne::UCustomInGameModuleBravoOne()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UCustomInGameModuleBravoOne"));
}

UCustomInGameModuleBravoTwo::UCustomInGameModuleBravoTwo()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UCustomInGameModuleBravoTwo"));
}

UCustomInGameModuleCharlieOne::UCustomInGameModuleCharlieOne()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UCustomInGameModuleCharlieOne"));
}

UCustomInGameModuleWillBeFail::UCustomInGameModuleWillBeFail()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UCustomInGameModuleWillBeFail"));
}

UCustomButBaseNameHasUser::UCustomButBaseNameHasUser()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructor of UCustomButBaseNameHasUser"));

	const FString AmITemplate = IsTemplate() ? FString(TEXT("Template")) : FString(TEXT("NOT Template"));
	FString AmICDO = FString(TEXT("CDO_Unknown"));
	FString NameOfCDO = FString(TEXT("ConfigObjectName_Unknown"));

	UClass* MyClass = GetClass();
	if (IsValid(MyClass))
	{
		UCustomButBaseNameHasUser* CDOofMe = GetClass()->GetDefaultObject<UCustomButBaseNameHasUser>();
		if (IsValid(CDOofMe))
		{
			AmICDO = CDOofMe == this ? FString(TEXT("CDO")) : FString(TEXT("NOT CDO"));
			NameOfCDO = CDOofMe->ConfigObjectName;		
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("UCustomButBaseNameHasUser Ctor Status: Template:%s / AmICDO:%s / ConfigObjectNameOfCDO: %s / MyConfigObjectName: %s"), *AmITemplate, *AmICDO, *NameOfCDO, *ConfigObjectName );
}


//Without this preprocessor, packaging will fail.
#if WITH_EDITOR  	
void UConfigEditorConfigInGameModule::SomeFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("SomeFunction is called."));
}
#endif



UE_ENABLE_OPTIMIZATION



