#pragma once

#include <QtCore\QAbstractItemModel>
#include <QtCore\QModelIndex>
#include <QtCore\QVariant>

#include "TreeItem.h"
#include "ObjectTreeModel.h"

class FileTreeModel : public QAbstractItemModel
{

public:
    explicit FileTreeModel(std::shared_ptr<ObjectTreeModel> object_model, QObject* parent = nullptr);
    ~FileTreeModel();

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
    bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
    bool moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent, int destinationChild) override;
    std::vector<QModelIndex> getMainChildren(int column);
    QModelIndex getLastRootChildren(int column);
    std::vector<QModelIndex> getItemChildren(const QModelIndex& parent, int column);
    void clearAll();
    int deltaIndexToLast(QModelIndex itemIndex);
    bool insertMainRow(int position, std::shared_ptr<GeoLayer> geoLayer, const QModelIndex& parent = QModelIndex());
    QStringList getAllFilePaths();
    QString titleGeoTypeChild(const QModelIndex& index) const;
    QIcon iconGeoTypeChild(const QString& type) const;
    bool isMainItem(const QModelIndex& index);
    
private:
    void setChecked(const QModelIndex& index, bool status);
    TreeItem* getItem(const QModelIndex& index) const;
    TreeItem* rootItem;
    std::shared_ptr<ObjectTreeModel> objectTreeModel;
};