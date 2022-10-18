#include "TreeItem.h"

TreeItem::TreeItem(const QList<QVariant>& data, TreeItem* parent) : itemData(data), parentItem(parent)
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

QList<TreeItem*> TreeItem::getChildren()
{
    return childItems;
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
