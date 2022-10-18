#pragma once

#include <QtWidgets\QTreeView>
#include <QtWidgets\QMenu>
#include <QtWidgets\QPushButton>

#include "../Models/FileTreeModel.h"

class MpFileTreeview : public QTreeView
{
	enum class MoveTreeItem
	{
		moveUp = 1 << 0,
		moveDown = 1 << 1,
		moveOnce = 1 << 2,
		moveMany = 1 << 3
	};

	friend MoveTreeItem operator|(MoveTreeItem lhs, MoveTreeItem rhs)
	{
		return static_cast<MoveTreeItem>(static_cast<std::underlying_type<MoveTreeItem>::type>(lhs) |
										 static_cast<std::underlying_type<MoveTreeItem>::type>(rhs));
	};

	friend MoveTreeItem operator&(MoveTreeItem lhs, MoveTreeItem rhs)
	{
		return static_cast<MoveTreeItem>(static_cast<std::underlying_type<MoveTreeItem>::type>(lhs) &
										 static_cast<std::underlying_type<MoveTreeItem>::type>(rhs));
	};

	std::shared_ptr<FileTreeModel> fileTreeModel;

	void addButton(int column, QString tooltip, QIcon icon, void(MpFileTreeview::* slotName)());
	void addButtonExtension();
	void addColorPickers();
	void setupMenuExtension(QPushButton* button);
	void moveItem(MoveTreeItem moveFlags);

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
	void changeColor(QPushButton* button);

public:
	explicit MpFileTreeview(std::shared_ptr<FileTreeModel> fileModel, QWidget* parent = nullptr);

};

