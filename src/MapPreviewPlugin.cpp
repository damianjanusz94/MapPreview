#include "MapPreviewPlugin.h"
#include <string>

std::shared_ptr<MapPreviewPlugin> mapPreviewPlugin;

std::shared_ptr<NppPlugin> createPlugin(HANDLE hModule)
{
	mapPreviewPlugin = std::make_shared<MapPreviewPlugin>(hModule);
	return mapPreviewPlugin;
}

void destroyPlugin() 
{
	mapPreviewPlugin.reset();
}

MapPreviewPlugin::MapPreviewPlugin(HANDLE hModule) : hModule(hModule)
{
	mapPreviewWindow = std::make_shared<MapPreviewWindow>(hModule);
	commandShowHide = std::make_unique<CommandShowHide>(mapPreviewWindow);
}

const TCHAR* MapPreviewPlugin::getName() 
{
	return _T("MapPreview");
}

void MapPreviewPlugin::Initialize(NppData nppDataH) 
{
	this->nppData = nppDataH;
	InitializeDependencies();
	InitializeCommands();
}

void MapPreviewPlugin::InitializeCommands()
{
	TCHAR command1[100];
	_tcscpy_s(command1, _countof(command1), _T("Show/Hide window"));
	setCommand(0, command1, commandShowHideActionExecutorAdapter, &*commandShowHide->getShortcutKey(), false);
}

void MapPreviewPlugin::InitializeDependencies()
{
	mapPreviewWindow->Initialize(nppData);
	commandShowHide->Initialize();
}

const size_t MapPreviewPlugin::getNumberOfActions() 
{
	return 1;
}

void commandShowHideActionExecutorAdapter() 
{
	mapPreviewPlugin->commandShowHideActionExecutor();
}

void MapPreviewPlugin::commandShowHideActionExecutor()
{
	commandShowHide->Execute();
}


