#pragma once

#include <QtWidgets\QTreeView>

#include "../Models/FileTreeModel.h"

class MpFileTreeview : public QTreeView
{
	std::unique_ptr<FileTreeModel> fileTreeModel;

	void addButton(int column, QString tooltip, QIcon icon, void(MpFileTreeview::* slotName)());

private slots:
	void refreshRow();
	void removeRow();

public:
	explicit MpFileTreeview(QWidget* parent = nullptr);

};

