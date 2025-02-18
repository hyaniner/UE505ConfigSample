// https://github.com/hyaniner/UE505ConfigSample

#include "ConfigTestEnginePlugin.h"

#define LOCTEXT_NAMESPACE "FConfigTestEnginePluginModule"

UE_DISABLE_OPTIMIZATION

void FConfigTestEnginePluginModule::StartupModule()
{
	UE_LOG(LogTemp, Warning, TEXT("FConfigTestEnginePluginModule::StartupModule is called."));	
}

void FConfigTestEnginePluginModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

UE_ENABLE_OPTIMIZATION

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FConfigTestEnginePluginModule, ConfigTestEnginePlugin)


