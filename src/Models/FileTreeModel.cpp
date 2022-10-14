#include "FileTreeModel.h"

FileTreeModel::FileTreeModel(const QString& data, QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem = new FileTreeItem({ tr("1"), tr("2"), tr("3"), tr("4")});
    setupModelData(data.split('\n'), rootItem);
}

FileTreeModel::~FileTreeModel()
{
    delete rootItem;
}

int FileTreeModel::columnCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return static_cast<FileTreeItem*>(parent.internalPointer())->columnCount();
    return rootItem->columnCount();
}

std::vector<QModelIndex> FileTreeModel::getMainChildren(int column)
{
    std::vector<QModelIndex> childrenIndexes;

    auto childrenList = rootItem->getChildren();
    for (auto child : childrenList)
    {
        childrenIndexes.push_back(createIndex(child->row(), column, child));
    }

    return childrenIndexes;
}

std::vector<QModelIndex> FileTreeModel::getItemChildren(const QModelIndex& parent, int column)
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

bool FileTreeModel::removeRows(int position, int rows, const QModelIndex& parent)
{
    FileTreeItem* parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem->removeChildren(position, rows);
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
    FileTreeItem* destinationItem = getItem(destinationParent);
    if (destinationItem == nullptr)
        return result;

    int position = destinationChild;
    for (int row = sourceRow; row < sourceRow + count; ++row)
    {
        QModelIndex index = this->index(row, 0, sourceParent);
        FileTreeItem* item = getItem(index);
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
}

QVariant FileTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    FileTreeItem* item1 = static_cast<FileTreeItem*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 0)
    {
        return static_cast<int>(item1->isChecked() ? Qt::Checked : Qt::Unchecked);
    }
    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    FileTreeItem* item = getItem(index);

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

    FileTreeItem* parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<FileTreeItem*>(parent.internalPointer());

    FileTreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex FileTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    FileTreeItem* childItem = static_cast<FileTreeItem*>(index.internalPointer());
    FileTreeItem* parentItem = childItem->getParentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int FileTreeModel::rowCount(const QModelIndex& parent) const
{
    FileTreeItem* parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<FileTreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}

void FileTreeModel::setupModelData(const QStringList& lines, FileTreeItem* parent)
{
    QList<FileTreeItem*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            position++;
        }

        const QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            const QStringList columnStrings =
                lineData.split(QLatin1Char('\t'), Qt::SkipEmptyParts);
            QList<QVariant> columnData;
            columnData.reserve(columnStrings.count());
            for (const QString& columnString : columnStrings)
                columnData << columnString;

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount() - 1);
                    indentations << position;
                }
            }
            else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new FileTreeItem(columnData, parents.last()));
        }
        ++number;
    }
}

FileTreeItem* FileTreeModel::getItem(const QModelIndex& index) const
{
    if (index.isValid()) 
    {
        FileTreeItem* item = static_cast<FileTreeItem*>(index.internalPointer());
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
        FileTreeItem* item = getItem(index);
        setChecked(index, !item->isChecked());
        return true;
    }
    
    return false;
}

void FileTreeModel::setChecked(const QModelIndex& index, bool status)
{
    if (index.isValid())
    {
        FileTreeItem* item = getItem(index);
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