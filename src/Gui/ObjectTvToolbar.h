#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QPushButton>
#include <QtCore\QDir>

#include "MpObjectTreeview.h"
#include "MessageWindow.h"

class ObjectTvToolbar : public QToolBar
{
	QPushButton* colorBtn;

	std::shared_ptr<MessageWindow> msgWindow;
	std::weak_ptr<MpObjectTreeview> objectTreeview;

	void setupColorBtn();

public:
	explicit ObjectTvToolbar(std::weak_ptr<MpObjectTreeview> objectTv, std::shared_ptr<MessageWindow> messageWindow, QWidget* parent = nullptr);
};