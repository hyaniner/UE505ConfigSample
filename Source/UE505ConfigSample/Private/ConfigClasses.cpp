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


//Without this preprocessor, packaging will fail.
#if WITH_EDITOR  	
void UConfigEditorConfigInGameModule::SomeFunction()
{
	UE_LOG(LogTemp, Warning, TEXT("SomeFunction is called."));
}
#endif



UE_ENABLE_OPTIMIZATION



