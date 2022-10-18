#pragma once

#include <QtWidgets\QTreeView>

#include "../Models/ObjectTreeModel.h"

class MpObjectTreeview : public QTreeView
{
	std::unique_ptr<ObjectTreeModel> objectTreeModel;

public:
	explicit MpObjectTreeview(QWidget* parent = nullptr);
};

