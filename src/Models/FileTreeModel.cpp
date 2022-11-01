#include "FileTreeModel.h"
#include "FileHelper.h"

#include<QtCore\QDir>
#include<QtGui\QIcon>

#include "../Models/GeoLayer.h"

using namespace Enums;

FileTreeModel::FileTreeModel(std::shared_ptr<ObjectTreeModel> object_model, QObject* parent)
    : objectTreeModel(object_model), QAbstractItemModel(parent)
{
    rootItem = new TreeItem({ tr("1"), tr("2"), tr("3"), tr("4")}, nullptr);
}

FileTreeModel::~FileTreeModel()
{
    delete rootItem;
}

int FileTreeModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

QList<QModelIndex> FileTreeModel::getMainChildren(int column)
{
    QList<QModelIndex> childrenIndexes;

    auto childrenList = rootItem->getChildren();
    for (auto child : childrenList)
    {
        childrenIndexes.push_back(createIndex(child->row(), column, child));
    }

    return childrenIndexes;
}

QModelIndex FileTreeModel::getLastRootChildren(int column)
{
    auto childrenList = rootItem->getChildren();
    if (childrenList.size() > 0)
        return createIndex(childrenList.last()->row(), column, childrenList.last());
    else
        return QModelIndex();
}

QList<QModelIndex> FileTreeModel::getItemChildren(const QModelIndex& parent, int column)
{
    QList<QModelIndex> childrenIndexes;

    auto item = getItem(parent);
    auto childrenList = item->getChildren();
    for (auto child : childrenList)
    {
        childrenIndexes.push_back(createIndex(child->row(), column, child));
    }

    return childrenIndexes;
}

std::shared_ptr<GeoLayer> FileTreeModel::getIndexGeoLayer(const QModelIndex& index)
{
    auto item = getItem(index);
    return item->geoLayer;
}

bool FileTreeModel::insertMainRow(int position, std::shared_ptr<GeoLayer> geoLayer, const QModelIndex& parent)
{
    TreeItem* parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position);
    const bool success = parentItem->insertChildren(position, rootItem->columnCount(), geoLayer);
    endInsertRows();

    return success;
}

bool FileTreeModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    TreeItem* parentItem = getItem(parent);
    if (!parentItem)
        return false;

    QStringList filePaths;
    for (auto item : parentItem->getChildren(position, rows))
    {
        filePaths.append(item->getFilePath());
    }

    beginRemoveRows(parent, position, position + rows - 1);
    bool success = parentItem->removeChildren(position, rows);
    if (success)
    {
        success = objectTreeModel->removeFiles(filePaths);
    }
    endRemoveRows();

    return success;
}

bool FileTreeModel::moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent, int destinationChild)
{
    if (destinationChild < 0 || destinationChild > this->rowCount())
    {
        return false;
    }

    if (!beginMoveRows(QModelIndex(), sourceRow, sourceRow + count - 1, QModelIndex(), destinationChild))
    {
        return false;
    }

    bool result = false;
    TreeItem* destinationItem = getItem(destinationParent);
    if (destinationItem == nullptr)
        return result;

    int position = destinationChild;
    for (int row = sourceRow; row < sourceRow + count; ++row)
    {
        QModelIndex index = this->index(row, 0, sourceParent);
        TreeItem* item = getItem(index);
        if (item == nullptr)
            continue;
        result |= destinationItem->moveChildren(item, position);
        ++position;
    }
    endMoveRows();
    return result;
}

void FileTreeModel::clearAll()
{
    beginResetModel();
    rootItem->clearChildren();
    endResetModel();

    objectTreeModel->clearAll();
}

QVariant FileTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem* item1 = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 0)
    {
        return static_cast<int>(item1->isChecked() ? Qt::Checked : Qt::Unchecked);
    }

    if (role == Qt::DecorationRole)
    {
        auto type = titleGeoTypeChild(index);
        if (!type.isEmpty())
            return iconGeoTypeChild(type);
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem* item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags FileTreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant FileTreeModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex FileTreeModel::index(int row, int column, const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex FileTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->getParentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int FileTreeModel::rowCount(const QModelIndex& parent) const
{
    TreeItem* parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

TreeItem* FileTreeModel::getItem(const QModelIndex& index) const
{
    if (index.isValid()) 
    {
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}


bool FileTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    Q_UNUSED(value);

    if (role == Qt::CheckStateRole)
    {
        TreeItem* item = getItem(index);
        setChecked(index, !item->isChecked());
        return true;
    }
    
    return false;
}

void FileTreeModel::setChecked(const QModelIndex& index, bool status)
{
    if (index.isValid())
    {
        TreeItem* item = getItem(index);
        item->setChecked(status);
        emit dataChanged(index, index);
    }

    if (!this->hasChildren(index))
    {
        return;
    }

    int rows = this->rowCount(index);
    for (int i = 0; i < rows; ++i)
        setChecked(this->index(i, 0, index), status);
}


int FileTreeModel::deltaIndexToLast(QModelIndex itemIndex)
{
    if (!itemIndex.isValid())
    {
        return 0;
    }

    int currRow = itemIndex.row();
    int rowCount = this->rowCount();

    if (currRow + 1 == rowCount)
    {
        return currRow;
    }

    return rowCount - currRow;
}


QStringList FileTreeModel::getAllFilePaths()
{
    QStringList filePaths;

    auto mainItems = rootItem->getChildren();
    for (const auto& item : mainItems)
    {
        filePaths.append(item->getFilePath());
    }

    return filePaths;
}

QString FileTreeModel::titleGeoTypeChild(const QModelIndex& index) const
{
    auto item = getItem(index);
    if (item->childCount() == 0)
    {
        return item->data(0).toString();
    }

    return QString();
}

QIcon FileTreeModel::iconGeoTypeChild(const QString& type) const
{
    if (type == "Point")
    {
        return QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\point-48.png");
    }
    else if (type == "Line")
    {
        return QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\line-48.png");
    }
    else if (type == "Polygon")
    {
        return QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\polygon-48.png");
    }

    return QIcon();
}

bool FileTreeModel::isMainItem(const QModelIndex& index)
{
    auto searchedItem = static_cast<TreeItem*>(index.internalPointer());
    auto mainItems = rootItem->getChildren();
    for (const auto item : mainItems)
    {
        if (item == searchedItem)
            return true;
    }

    return false;
}

void FileTreeModel::setColorsGeoLayer(const QModelIndex& index, QColor color)
{
    auto geoLayer = getIndexGeoLayer(index);
    geoLayer->setColor(color, GeoType::POINT);
    geoLayer->setColor(color, GeoType::LINE);
    geoLayer->setColor(color, GeoType::POLYGON);
}
