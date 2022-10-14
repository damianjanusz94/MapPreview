#include "MpFileTreeview.h"

#include <QtCore\QFile>
#include <QtCore\QDir>
#include <QtWidgets\QHeaderView>

MpFileTreeview::MpFileTreeview(QWidget* parent) : QTreeView(parent)
{
    QFile file("C:\\Users\\d.janusz\\Documents\\GitDJ\\default.txt");
    file.open(QIODevice::ReadOnly);
    fileTreeModel = std::make_unique<FileTreeModel>(file.readAll(), this);
    file.close();

    setModel(fileTreeModel.get());
    setHeaderHidden(true);
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    header()->setStretchLastSection(false);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setStyleSheet("selection-background-color: rgb(240, 240, 240);selection-color: black");

    addButtonExtension();
    addButton(2, "Refresh", QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\refresh-24.png"), &MpFileTreeview::refreshRow);
    addButton(3, "Remove", QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\remove-24.png"), &MpFileTreeview::removeRow);
}

void MpFileTreeview::addButton(int column, QString tooltip, QIcon icon, void(MpFileTreeview::* slotName)())
{
    auto mainChildIndexes = fileTreeModel->getMainChildren(column);
    for (const auto& child : mainChildIndexes)
    {
        auto button = new QPushButton();
        button->setIcon(icon);
        button->setFlat(true);
        button->setToolTip("Refresh");
        setIndexWidget(child, button);
        connect(button, &QPushButton::released, this, slotName);
    }
}

void MpFileTreeview::addButtonExtension()
{
    auto mainChildIndexes = fileTreeModel->getMainChildren(1);
    for (const auto& child : mainChildIndexes)
    {
        auto button = new QPushButton("unknown");
        button->setFlat(true);
        button->setToolTip("File type");
        setupMenuExtension(button);
        setIndexWidget(child, button);
    }
}

void MpFileTreeview::setupMenuExtension(QPushButton* button)
{
    auto menuExtension = new QMenu();

    QAction* unknownAction = new QAction("unknown", button);
    QAction* geojsonAction = new QAction("GEOJSON", button);
    QAction* wkbAction = new QAction("WKB", button);
    QAction* wktAction = new QAction("WKT", button);
    
    connect(unknownAction, &QAction::triggered, this, [this, unknownAction, button] { changeExtension(unknownAction, button); });
    connect(geojsonAction, &QAction::triggered, this, [this, geojsonAction, button] { changeExtension(geojsonAction, button); });
    connect(wkbAction, &QAction::triggered, this, [this, wkbAction, button] { changeExtension(wkbAction, button); });
    connect(wktAction, &QAction::triggered, this, [this, wktAction, button] { changeExtension(wktAction, button); });
    
    menuExtension->addAction(unknownAction);
    menuExtension->addAction(geojsonAction);
    menuExtension->addAction(wkbAction);
    menuExtension->addAction(wktAction);

    button->setMenu(menuExtension);
}

void MpFileTreeview::refreshRow()
{
}

void MpFileTreeview::removeRow()
{
    const QModelIndex index = this->selectionModel()->currentIndex();
    this->model()->removeRow(index.row(), index.parent());
}

void MpFileTreeview::refreshAll()
{
}

void MpFileTreeview::removeAll()
{
    fileTreeModel->clearAll();
}

void MpFileTreeview::moveUp()
{
    moveItem(MoveTreeItem::moveUp | MoveTreeItem::moveOnce);
}

void MpFileTreeview::moveDown()
{
    moveItem(MoveTreeItem::moveDown | MoveTreeItem::moveOnce);
}

void MpFileTreeview::moveToFirst()
{
    moveItem(MoveTreeItem::moveUp | MoveTreeItem::moveMany);
}

void MpFileTreeview::moveToLast()
{
    moveItem(MoveTreeItem::moveDown | MoveTreeItem::moveMany);
}

void MpFileTreeview::moveItem(MoveTreeItem moveFlags)
{
    if (!this->selectionModel()->hasSelection())
    {
        return;
    }

    int move = 0;
    const QModelIndex index = this->selectionModel()->currentIndex();

    if (index.parent().internalPointer() != nullptr)
    {
       return;
    }

    if (static_cast<bool>(moveFlags & MoveTreeItem::moveOnce))
    {
        if (static_cast<bool>(moveFlags & MoveTreeItem::moveUp))
        {
            move = index.row() - 1;
        }
        else
        {
            move = index.row() + 2;
        }
    }
    else
    {
        if (static_cast<bool>(moveFlags & MoveTreeItem::moveUp))
        {
            move = 0;
        }
        else
        {
            move = fileTreeModel->deltaIndexToLast(index);
        }
    }

    if (move == index.row())
    {
        return;
    }

    this->model()->moveRow(index.parent(), index.row(), index.parent(), move);
}


void MpFileTreeview::changeExtension(QAction* action, QPushButton* button)
{
    button->setText(action->text());
}

