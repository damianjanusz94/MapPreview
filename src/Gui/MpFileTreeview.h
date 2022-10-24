#pragma once

#include <QtWidgets\QTreeView>
#include <QtWidgets\QMenu>
#include <QtWidgets\QPushButton>

#include "../Models/FileTreeModel.h"
#include "../Models/GeoLayer.h"

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

	static const int TEXT_COLUMN = 0;
	static const int EXTENSION_COLUMN = 1;
	static const int REFRESH_COLUMN = 2;
	static const int REMOVE_COLUMN = 3;

	std::shared_ptr<FileTreeModel> fileTreeModel;

	void addButton(const QModelIndex& index, QString tooltip, QIcon icon, void(MpFileTreeview::* slotName)());
	void addButtonExtension(const QModelIndex& index, const QString& fileExtension);
	void addColorPickers(const QModelIndex& index, std::shared_ptr<GeoLayer> geoLayer);
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
	void changeColor(QPushButton* button, std::shared_ptr<GeoLayer> geo_layer, GeoType geo_type);
	void setColorForItems();

public:
	explicit MpFileTreeview(std::shared_ptr<FileTreeModel> fileModel, QWidget* parent = nullptr);
	void addFileItem(const QString& filePath, std::shared_ptr<GeoLayer> geoLayer);
};

