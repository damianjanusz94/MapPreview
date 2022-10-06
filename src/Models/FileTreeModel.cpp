#include "FileTreeModel.h"

FileTreeModel::FileTreeModel(const QString& data, QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem = new FileTreeItem({ tr("") });
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
