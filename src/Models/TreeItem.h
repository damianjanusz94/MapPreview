#pragma once

#include <QtCore\QVariant>
#include <QtCore\QList>

class TreeItem
{
public:
    explicit TreeItem(const QList<QVariant>& data, TreeItem* parentItem = nullptr);
    ~TreeItem();

    void appendChild(TreeItem* child);

    TreeItem* child(int row);
    QList<TreeItem*> getChildren();
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    TreeItem* getParentItem();
    void setChecked(bool set);
    bool isChecked();
    bool removeChildren(int position, int count);
    bool moveChildren(TreeItem* child, int position);
    void clearChildren();

private:
    QList<TreeItem*> childItems;
    QList<QVariant> itemData;
    TreeItem* parentItem;
    bool checked = false;
};