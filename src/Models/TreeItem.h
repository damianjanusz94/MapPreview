#pragma once

#include <QtCore\QVariant>
#include <QtCore\QList>

#include "../Enums/GeoType.h"

class GeoLayer;

class TreeItem : public QObject
{
    Q_OBJECT

public:
    explicit TreeItem(const QList<QVariant>& data, std::shared_ptr<GeoLayer> geolayer, TreeItem* parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child);

    TreeItem* child(int row);
    TreeItem* getLastChild();
    QList<TreeItem*> getChildren();
    QList<TreeItem*> getChildren(int row, int count);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    void setData(int column, QVariant value);
    int row() const;
    TreeItem* getParentItem();
    void setChecked(bool set);
    bool isChecked();
    bool insertChildren(int position, int columns, std::shared_ptr<GeoLayer> geo_layer);
    bool insertChildrenObject(int position, int columns, const QString& filePath, std::shared_ptr<GeoLayer> geo_layer, Enums::GeoType geoType);
    bool removeChildren(int position, int count);
    bool moveChildren(TreeItem* child, int position);
    void clearChildren();
    QString getFilePath();
    void insertGeoChild(int columns, const QString& title);
    Enums::GeoType getGeoType();

    std::shared_ptr<GeoLayer> geoLayer;

public slots:
    void onColorChanged(const QColor& color);

signals:
    void dataChanged();

private:
    QList<TreeItem*> childItems;
    QList<QVariant> itemData;
    TreeItem* parentItem;
    bool checked = true;
};