#include "MpObjectTreeview.h"

#include <QtCore\QRandomGenerator>
#include <QtWidgets\QHeaderView>
#include <QtWidgets\QColorDialog>

#include "../Models/ColorDelegate.h"

MpObjectTreeview::MpObjectTreeview(std::shared_ptr<ObjectTreeModel> object_model, QWidget* parent) : QTreeView(parent), objectTreeModel(object_model)
{
    setItemDelegate(new ColorDelegate());
    setModel(objectTreeModel.get());
    setHeaderHidden(true);
    setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header()->setStretchLastSection(false);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    //setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setStyleSheet("selection-background-color: rgb(240, 240, 240);selection-color: black");
}

void MpObjectTreeview::addFileItem(const QString& filePath, std::shared_ptr<GeoLayer> geoLayer)
{
    if (!objectTreeModel->insertFileChild(filePath, geoLayer))
        return;

   // addColorPickers(objectTreeModel->getLastGeoFiles(EXTENSION_COLUMN), geoLayer);
}

void MpObjectTreeview::addColorPickers(const QList<QModelIndex> indexList, std::shared_ptr<GeoLayer> geoLayer)
{
    if (indexList.count() != 3)
        return;

    QColor colorPoint = geoLayer->getColor(GeoType::POINT);
    QColor colorLine = geoLayer->getColor(GeoType::LINE);
    QColor colorPolygon = geoLayer->getColor(GeoType::POLYGON);

    auto buttonPoint = new QPushButton();
    auto buttonLine = new QPushButton();
    auto buttonPolygon = new QPushButton();

    buttonPoint->setStyleSheet("background-color : " + colorPoint.name());
    buttonLine->setStyleSheet("background-color : " + colorLine.name());
    buttonPolygon->setStyleSheet("background-color : " + colorPolygon.name());

    setIndexWidget(indexList[0], buttonPoint);
    setIndexWidget(indexList[1], buttonLine);
    setIndexWidget(indexList[2], buttonPolygon);
        
    connect(buttonPoint, &QPushButton::released, this, [this, buttonPoint, geoLayer] { changeColor(buttonPoint, geoLayer, GeoType::POINT); });
    connect(buttonLine, &QPushButton::released, this, [this, buttonLine, geoLayer] { changeColor(buttonLine, geoLayer, GeoType::LINE); });
    connect(buttonPolygon, &QPushButton::released, this, [this, buttonPolygon, geoLayer] { changeColor(buttonPolygon, geoLayer, GeoType::POLYGON); });

    geoLayer->setColorButtonConnection(buttonPoint, buttonLine, buttonPolygon);
}

void MpObjectTreeview::changeColor(QPushButton* button, std::shared_ptr<GeoLayer> geo_layer, GeoType geo_type)
{
    QColor oldColor = button->palette().window().color();
    QColor newColor = QColorDialog::getColor(oldColor, nullptr, "Pick a color");
    if (!newColor.isValid())
    {
        return;
    }

    if (newColor != oldColor)
    {
        geo_layer->setColor(newColor, geo_type);
    }
}

void MpObjectTreeview::setColorForItems()
{
    if (!this->selectionModel()->hasSelection())
    {
        return;
    }

    const QModelIndex index = this->selectionModel()->currentIndex();
    if (!objectTreeModel->isMainItem(index))
    {
        return;
    }

    QColor newColor = QColorDialog::getColor(Qt::white, nullptr, "Pick a color");
    if (!newColor.isValid())
    {
        return;
    }

    objectTreeModel->setColorsGeoLayer(index, newColor);
}

void MpObjectTreeview::connectButtonWithSelection(QPushButton* button)
{
    if (button == nullptr)
        return;

    connect(this->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this, button] { onSelectionChanged(button); });
}

void MpObjectTreeview::onSelectionChanged(QPushButton* button)
{
    if (button == nullptr)
        return;


    if (!this->selectionModel()->hasSelection())
    {
        button->setEnabled(false);
        return;
    }

    const QModelIndex index = this->selectionModel()->currentIndex();
    if (objectTreeModel->isMainItem(index))
    {
        button->setEnabled(true);
    }
    else
    {
        button->setEnabled(false);
    }

}
