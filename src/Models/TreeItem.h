#pragma once

#include <QtCore\QVariant>
#include <QtCore\QList>

class GeoLayer;

class TreeItem
{
public:
    explicit TreeItem(const QList<QVariant>& data, std::shared_ptr<GeoLayer> geolayer, TreeItem* parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child);

    TreeItem* child(int row);
    QList<TreeItem*> getChildren();
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* getParentItem();
    void setChecked(bool set);
    bool isChecked();
    bool insertChildren(int position, int columns, const QString& filePath);
    bool removeChildren(int position, int count);
    bool moveChildren(TreeItem* child, int position);
    void clearChildren();
    QString getFilePath();
    void insertGeoChild(int columns, const QString& title);

private:
    QList<TreeItem*> childItems;
    QList<QVariant> itemData;
    TreeItem* parentItem;
    std::shared_ptr<GeoLayer> geoLayer;
    bool checked = true;
};