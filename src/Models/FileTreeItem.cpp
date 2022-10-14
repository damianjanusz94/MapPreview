#include "FileTreeItem.h"

FileTreeItem::FileTreeItem(const QList<QVariant>& data, FileTreeItem* parent) : itemData(data), parentItem(parent)
{
}

FileTreeItem::~FileTreeItem()
{
    qDeleteAll(childItems);
}

void FileTreeItem::appendChild(FileTreeItem* item)
{
    childItems.append(item);
}

FileTreeItem* FileTreeItem::child(int row)
{
    if (row < 0 || row >= childItems.size())
        return nullptr;
    return childItems.at(row);
}

QList<FileTreeItem*> FileTreeItem::getChildren()
{
    return childItems;
}

int FileTreeItem::childCount() const
{
    return childItems.count();
}

int FileTreeItem::columnCount() const
{
    return itemData.count();
}

QVariant FileTreeItem::data(int column) const
{
    if (column < 0 || column >= itemData.size())
        return QVariant();
    return itemData.at(column);
}

FileTreeItem* FileTreeItem::getParentItem()
{
    return parentItem;
}

void FileTreeItem::setChecked(bool set)
{
    checked = set;
}

bool FileTreeItem::isChecked()
{
    return checked;
}

int FileTreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<FileTreeItem*>(this));

    return 0;
}

bool FileTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete childItems.takeAt(position);

    return true;
}

bool FileTreeItem::moveChildren(FileTreeItem* child, int position)
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

void FileTreeItem::clearChildren()
{
    for (int row = 0; row < childItems.size(); ++row)
        delete childItems.at(row);
    childItems.clear();
}
