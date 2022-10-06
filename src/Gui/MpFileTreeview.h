#pragma once

#include <QtWidgets\QTreeView>

#include "../Models/FileTreeModel.h"

class MpFileTreeview : public QTreeView
{
	std::unique_ptr<FileTreeModel> fileTreeModel;

public:
	explicit MpFileTreeview(QWidget* parent = nullptr);
};

