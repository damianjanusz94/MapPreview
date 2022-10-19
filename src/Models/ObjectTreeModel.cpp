#include "ObjectTreeModel.h"

ObjectTreeModel::ObjectTreeModel(const QString& data, QObject* parent)
    : QAbstractItemModel(parent)
{
    rootItem = new TreeItem({ tr("1"), tr("2") }, nullptr);
    setupModelData(data.split('\n'), rootItem);
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

QVariant ObjectTreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    TreeItem* item1 = static_cast<TreeItem*>(index.internalPointer());

    if (role == Qt::CheckStateRole && index.column() == 0)
    {
        return static_cast<int>(item1->isChecked() ? Qt::Checked : Qt::Unchecked);
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

void ObjectTreeModel::setupModelData(const QStringList& lines, TreeItem* parent)
{
    QList<TreeItem*> parents;
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
            parents.last()->appendChild(new TreeItem(columnData, nullptr, parents.last()));
        }
        ++number;
    }
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
