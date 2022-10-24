#pragma once

#include <QtCore\QAbstractItemModel>
#include <QtCore\QModelIndex>
#include <QtCore\QVariant>

#include "TreeItem.h"
#include "../Models/GeoLayer.h"

class ObjectTreeModel : public QAbstractItemModel
{

public:
    explicit ObjectTreeModel(QObject* parent = nullptr);
    ~ObjectTreeModel();

    QVariant data(const QModelIndex& index, int role) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
        int role = Qt::DisplayRole) const override;
    QModelIndex index(int row, int column,
        const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;
    QList<QModelIndex> getMainChildren(int column);
    QList<QModelIndex> getItemChildren(const QModelIndex& parent, int column);
    bool insertFileChild(const QString& filePath, std::shared_ptr<GeoLayer> geoLayer);
    bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
    bool removeFiles(const QStringList& filePaths);
    bool removeFile(const QString& filePath);
    void clearAll();
    bool moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent, int destinationChild) override;
    QList<QModelIndex> getLastGeoFiles(int column);
    bool isMainItem(const QModelIndex& index) const;
    void setColorsGeoLayer(const QModelIndex& index, QColor color);

private:
    QModelIndex getLastItemChildren(TreeItem* item, int column);
    void setChecked(const QModelIndex& index, bool status);
    QIcon iconGeoType(const QModelIndex& index) const;
    TreeItem* getItem(const QModelIndex& index) const;
    TreeItem* rootItem;
};