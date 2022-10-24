#pragma once

#include <QtWidgets\QTreeView>
#include <QtWidgets\QPushButton>

#include "../Models/ObjectTreeModel.h"
#include "../Models/GeoLayer.h"

class MpObjectTreeview : public QTreeView
{
	static const int TEXT_COLUMN = 0;
	static const int EXTENSION_COLUMN = 1;

	std::shared_ptr<ObjectTreeModel> objectTreeModel;
	void changeColor(QPushButton* button, std::shared_ptr<GeoLayer> geo_layer, GeoType geo_type);

public:
	explicit MpObjectTreeview(std::shared_ptr<ObjectTreeModel> object_model, QWidget* parent = nullptr);
	void addFileItem(const QString& filePath, std::shared_ptr<GeoLayer> geoLayer);
	void addColorPickers(const QList<QModelIndex> indexList, std::shared_ptr<GeoLayer> geoLayer);
	void setColorForItems();
};

