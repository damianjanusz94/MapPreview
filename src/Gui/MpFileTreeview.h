#pragma once

#include <QtWidgets\QTreeView>

#include "../Models/FileTreeModel.h"

class MpFileTreeview : public QTreeView
{
	std::unique_ptr<FileTreeModel> fileTreeModel;

	void addButton(int column, QString tooltip, QIcon icon, void(MpFileTreeview::* slotName)());

public slots:
	void refreshRow();
	void removeRow();
	void refreshAll();
	void removeAll();

public:
	explicit MpFileTreeview(QWidget* parent = nullptr);

};

