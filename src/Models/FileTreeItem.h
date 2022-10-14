#pragma once

#include <QtCore\QVariant>
#include <QtCore\QList>

class FileTreeItem
{
public:
    explicit FileTreeItem(const QList<QVariant>& data, FileTreeItem* parentItem = nullptr);
    ~FileTreeItem();

    void appendChild(FileTreeItem* child);

    FileTreeItem* child(int row);
    QList<FileTreeItem*> getChildren();
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    FileTreeItem* getParentItem();
    void setChecked(bool set);
    bool isChecked();
    bool removeChildren(int position, int count);
    bool moveChildren(FileTreeItem* child, int position);
    void clearChildren();

private:
    QList<FileTreeItem*> childItems;
    QList<QVariant> itemData;
    FileTreeItem* parentItem;
    bool checked = false;
};