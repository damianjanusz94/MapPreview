#pragma once

#include "NppPlugin/NppPlugin.h"
#include "Commands/CommandShowHide.h"
#include "MapPreviewWindow.h"

class MapPreviewPlugin : public NppPlugin
{
private:
	HANDLE hModule;
	NppData nppData;

	std::unique_ptr<CommandShowHide> commandShowHide;
	std::shared_ptr<MapPreviewWindow> mapPreviewWindow;

public:
	MapPreviewPlugin(HANDLE hModule);

	const TCHAR* getName();
	const size_t getNumberOfActions();

	void Initialize(NppData nppDataH);
	void InitializeCommands();
	void InitializeDependencies();

	void commandShowHideActionExecutor();
};

void commandShowHideActionExecutorAdapter();
