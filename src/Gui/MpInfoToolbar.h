#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QLabel>

#include "MessageWindow.h"


class MpInfoToolbar : public QToolBar
{
	std::shared_ptr<MessageWindow> msgWindow;
public:
	explicit MpInfoToolbar(QWidget* parent, std::shared_ptr<MessageWindow> messageWindow);
};

