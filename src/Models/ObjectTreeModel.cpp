#include "ObjectTreeModel.h"

#include<QtCore\QDir>
#include<QtGui\QIcon>

ObjectTreeModel::ObjectTreeModel(QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem({ tr("1"), tr("2") }, nullptr);
    
    QStringList objNames{ "Point", "Line", "Polygon" };
    for (const auto& name : objNames)
    {
        QList<QVariant> data;
        data.reserve(2);
        data << name;
        rootItem->appendChild(new TreeItem(data, nullptr, rootItem));
    }
}

ObjectTreeModel::~ObjectTreeModel()
{
    delete rootItem;
}

int ObjectTreeModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

std::vector<QModelIndex> ObjectTreeModel::getMainChildren(int column)
{
    std::vector<QModelIndex> childrenIndexes;

    auto childrenList = rootItem->getChildren();
    for (auto child : childrenList)
    {
        childrenIndexes.push_back(createIndex(child->row(), column, child));
    }

    return childrenIndexes;
}

std::vector<QModelIndex> ObjectTreeModel::getItemChildren(const QModelIndex& parent, int column)
{
    std::vector<QModelIndex> childrenIndexes;

    auto item = getItem(parent);
    auto childrenList = item->getChildren();
    for (auto child : childrenList)
    {
        childrenIndexes.push_back(createIndex(child->row(), column, child));
    }

    return childrenIndexes;
}

bool ObjectTreeModel::insertFileChild(const QString& filePath)
{
    auto mainItemList = rootItem->getChildren();
    for (auto item : mainItemList)
    {
        auto lastchildIndex = getLastItemChildren(item, 0);
        int position = lastchildIndex.row() + 1;
        auto parentIndex = createIndex(item->row(), 0, item);
        
        beginInsertRows(parentIndex, position, position);
        const bool success = item->insertChildrenObject(position, rootItem->columnCount(), filePath);
        if (!success)
            return false;
        endInsertRows();
    }
    
    return true;
}

QVariant ObjectTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem* item1 = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 0)
    {
        return static_cast<int>(item1->isChecked() ? Qt::Checked : Qt::Unchecked);
    }

    if (role == Qt::DecorationRole && index.column() == 0)
    {
        if (isMainItem(index))
        {
            return iconGeoType(index);
        }
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem* item = getItem(index);

    return item->data(index.column());
}

Qt::ItemFlags ObjectTreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable;
}

QVariant ObjectTreeModel::headerData(int section, Qt::Orientation orientation,
    int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex ObjectTreeModel::index(int row, int column, const QModelIndex& parent) const
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

QModelIndex ObjectTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem* parentItem = childItem->getParentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ObjectTreeModel::rowCount(const QModelIndex& parent) const
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

TreeItem* ObjectTreeModel::getItem(const QModelIndex& index) const
{
    if (index.isValid())
    {
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}


bool ObjectTreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
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

void ObjectTreeModel::setChecked(const QModelIndex& index, bool status)
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

bool ObjectTreeModel::isMainItem(const QModelIndex& index) const
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

QIcon ObjectTreeModel::iconGeoType(const QModelIndex& index) const
{
    auto item = getItem(index);
    QString type(item->data(0).toString());

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

QModelIndex ObjectTreeModel::getLastItemChildren(TreeItem* item, int column)
{
    auto childrenList = item->getChildren();
    if (childrenList.size() > 0)
        return createIndex(childrenList.last()->row(), column, childrenList.last());
    else
        return QModelIndex();
}

bool ObjectTreeModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    TreeItem* parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();

    return success;
}


bool ObjectTreeModel::removeFiles(const QStringList& filePaths)
{
    for (const auto& file : filePaths)
    {
        if (!removeFile(file))
            return false;
    }
    return true;
}

bool ObjectTreeModel::removeFile(const QString& filePath)
{
    auto mainItems = rootItem->getChildren();
    for (auto item : mainItems)
    {
        auto subItems = item->getChildren();
        for (auto subItem : subItems)
        {
            if (filePath == subItem->getFilePath())
            {
                QModelIndex parentIndex = createIndex(item->row(), 0, item);
                if (!removeRow(subItem->row(), parentIndex))
                    return false;
            }
        }
    }
    return true;
}

void ObjectTreeModel::clearAll()
{
    auto mainItems = rootItem->getChildren();
    for (auto item : mainItems)
    {
        beginResetModel();
        item->clearChildren();
        endResetModel();
    }
}

bool ObjectTreeModel::moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent, int destinationChild)
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
