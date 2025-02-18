// https://github.com/hyaniner/UE505ConfigSample

#pragma once

#include "Modules/ModuleManager.h"

class FConfigTestEnginePluginModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
