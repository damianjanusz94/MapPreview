#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QLabel>

#include "MessageWindow.h"


class MpInfoToolbar : public QToolBar
{
	std::shared_ptr<MessageWindow> msgWindow;
	QLabel* coordinatesLabel = nullptr;

public:
	explicit MpInfoToolbar(QWidget* parent, std::shared_ptr<MessageWindow> messageWindow);
	void setCoordinatesLabel(const QString& text);
};

