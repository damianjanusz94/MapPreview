#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QPushButton>
#include <QtCore\QDir>

#include "MpObjectTreeview.h"

class ObjectTvToolbar : public QToolBar
{
	QPushButton* colorBtn;

	std::weak_ptr<MpObjectTreeview> objectTreeview;

	void setupColorBtn();

public:
	explicit ObjectTvToolbar(std::weak_ptr<MpObjectTreeview> objectTv, QWidget* parent = nullptr);
};