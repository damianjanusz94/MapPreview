#pragma once

#include <QtWidgets\QTreeView>
#include <QtWidgets\QPushButton>

#include "../Models/ObjectTreeModel.h"
#include "../Models/GeoLayer.h"

class MpObjectTreeview : public QTreeView
{
	static const int TEXT_COLUMN = 0;
	static const int COLOR_COLUMN = 1;

	std::shared_ptr<ObjectTreeModel> objectTreeModel;

public slots:
	void onSelectionChanged(QPushButton* button);

public:
	explicit MpObjectTreeview(std::shared_ptr<ObjectTreeModel> object_model, QWidget* parent = nullptr);
	void addFileItem(const QString& filePath, std::shared_ptr<GeoLayer> geoLayer);
	void connectButtonWithSelection(QPushButton* button);
	void setColorForItems();
};

