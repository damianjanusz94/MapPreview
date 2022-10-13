#pragma once

#include <QtWidgets\QTreeView>
#include <QtWidgets\QMenu>
#include <QtWidgets\QPushButton>

#include "../Models/FileTreeModel.h"

class MpFileTreeview : public QTreeView
{
	std::unique_ptr<FileTreeModel> fileTreeModel;

	void addButton(int column, QString tooltip, QIcon icon, void(MpFileTreeview::* slotName)());
	void addButtonExtension();
	void setupMenuExtension(QPushButton* button);

public slots:
	void refreshRow();
	void removeRow();
	void refreshAll();
	void removeAll();
	void moveUp();
	void moveDown();
	void moveToFirst();
	void moveToLast();
	void changeExtension(QAction* action, QPushButton* button);


public:
	explicit MpFileTreeview(QWidget* parent = nullptr);

};

