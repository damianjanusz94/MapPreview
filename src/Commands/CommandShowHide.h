#pragma once

#include <memory>
#include "../NppPlugin/PluginInterface.h"	
#include "../MapPreviewWindow.h"

class CommandShowHide
{
private:
	std::weak_ptr<MapPreviewWindow> mapPreviewWindow;
	std::shared_ptr<ShortcutKey> shortcutKey;

public:
	CommandShowHide(std::weak_ptr<MapPreviewWindow> window) : mapPreviewWindow(window) {};

	void Initialize();
	void Execute();

	std::shared_ptr<ShortcutKey> getShortcutKey();
};