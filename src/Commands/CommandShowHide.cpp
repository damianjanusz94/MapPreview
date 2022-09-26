#include "CommandShowHide.h"

void CommandShowHide::Initialize()
{
	shortcutKey = std::make_shared<ShortcutKey>();

	shortcutKey->_isCtrl = false;
	shortcutKey->_isAlt = false;
	shortcutKey->_isShift = true;
	shortcutKey->_key = VK_F12;
}

void CommandShowHide::Execute()
{
	mapPreviewWindow.lock()->Display(!mapPreviewWindow.lock()->isVisible());
}

std::shared_ptr<ShortcutKey> CommandShowHide::getShortcutKey()
{
	return std::shared_ptr<ShortcutKey>();
}
