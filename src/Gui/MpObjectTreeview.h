#pragma once

#include <QtWidgets\QTreeView>

#include "../Models/ObjectTreeModel.h"

class MpObjectTreeview : public QTreeView
{
	std::shared_ptr<ObjectTreeModel> objectTreeModel;

public:
	explicit MpObjectTreeview(std::shared_ptr<ObjectTreeModel> object_model, QWidget* parent = nullptr);
	void addFileItems(const QStringList& filePaths);
	void addFileItem(const QString& filePath);
};

