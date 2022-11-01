#include "TreeItem.h"
#include "FileHelper.h"
#include "../Models/GeoLayer.h"

#include<QtCore\QDir>
#include<QtGui\QIcon>

using namespace Enums;

TreeItem::TreeItem(const QList<QVariant>& data, std::shared_ptr<GeoLayer> geolayer, TreeItem* parent) 
                  : itemData(data), parentItem(parent), geoLayer(geolayer)
{
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

void TreeItem::appendChild(TreeItem* item)
{
    childItems.append(item);
}

TreeItem* TreeItem::child(int row)
{
    if (row < 0 || row >= childItems.size())
        return nullptr;
    return childItems.at(row);
}

TreeItem* TreeItem::getLastChild()
{
    return childItems.last();
}

QList<TreeItem*> TreeItem::getChildren()
{
    return childItems;
}

QList<TreeItem*> TreeItem::getChildren(int row, int count)
{
    QList<TreeItem*> children;

    for (int i = 0; i < count; i++)
    {
        children.append(child(row + i));
    }

    return children;
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    if (column < 0 || column >= itemData.size())
        return QVariant();
    
    return itemData.at(column);
}

void TreeItem::setData(int column, QVariant value)
{
    if (column < 0 || column >= itemData.size())
        return;

    itemData[column] = value;
}

TreeItem* TreeItem::getParentItem()
{
    return parentItem;
}

void TreeItem::setChecked(bool set)
{
    checked = set;
}

bool TreeItem::isChecked()
{
    return checked;
}

int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

bool TreeItem::insertChildren(int position, int columns, std::shared_ptr<GeoLayer> geo_layer)
{
    if (position < 0 || position > childItems.size())
        return false;

    QList<QVariant> data;
    data.reserve(columns);
    data << geo_layer->getFileNameWoExt();
    TreeItem* item = new TreeItem(data, geo_layer, this);
    childItems.insert(position, item);
    item->insertGeoChild(columns, QString("Point"));
    item->insertGeoChild(columns, QString("Line"));
    item->insertGeoChild(columns, QString("Polygon"));

    return true;
}

bool TreeItem::insertChildrenObject(int position, int columns, const QString& filePath, std::shared_ptr<GeoLayer> geo_layer, GeoType geoType)
{
    if (position < 0 || position > childItems.size())
        return false;

    QList<QVariant> data;
    data.reserve(columns);
    data << FileHelper::getFileName(filePath);
    data << geo_layer->getColor(geoType);
    TreeItem* item = new TreeItem(data, geo_layer, this);
    childItems.insert(position, item);

    switch (geoType)
    {
        case GeoType::POINT:
            connect(geo_layer.get(), &GeoLayer::pointColorChanged, item, &TreeItem::onColorChanged);
            break;
        case GeoType::LINE:
            connect(geo_layer.get(), &GeoLayer::lineColorChanged, item, &TreeItem::onColorChanged);
            break;
        case GeoType::POLYGON:
            connect(geo_layer.get(), &GeoLayer::polygonColorChanged, item, &TreeItem::onColorChanged);
            break;
    };

    return true;
}

void TreeItem::insertGeoChild(int columns, const QString& title)
{
    QList<QVariant> data;
    data.reserve(columns);
    data << title;
    TreeItem* item = new TreeItem(data, geoLayer, this);
    appendChild(item);
}

GeoType TreeItem::getGeoType()
{
    QString type = this->data(0).toString();
    auto geoType = GeoType::UNDEFINED;
    if (type == "Point")
    {
        geoType = GeoType::POINT;
    }
    else if (type == "Line")
    {
        geoType = GeoType::LINE;
    }
    else if (type == "Polygon")
    {
        geoType = GeoType::POLYGON;
    }

    return geoType;
}

bool TreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool TreeItem::moveChildren(TreeItem* child, int position)
{
    if (child == nullptr)
        return false;
    if (child->parentItem == nullptr)
        return false;
    if (child->parentItem != this)
    {
        child->parentItem->childItems.removeOne(child);
        childItems.insert(position, child);
        child->parentItem = this;
    }
    else
    {
        int index = childItems.indexOf(child);
        if (position > index)
            position--;
        childItems.move(index, position);
    }
    return true;
}

void TreeItem::clearChildren()
{
    for (int row = 0; row < childItems.size(); ++row)
        delete childItems.at(row);
    childItems.clear();
}

QString TreeItem::getFilePath()
{
    if (geoLayer.get())
    {
        return geoLayer->getFilePath();
    }

    return QString("");
}

void TreeItem::onColorChanged(const QColor& color)
{
    setData(1, QVariant(color));
    emit dataChanged();
}