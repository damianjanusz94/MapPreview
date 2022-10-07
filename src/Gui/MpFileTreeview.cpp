#include "MpFileTreeview.h"

#include <QtCore\QFile>
#include <QtCore\QDir>
#include <QtWidgets\QPushButton>
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
    header()->setStretchLastSection(false);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    setSelectionMode(QAbstractItemView::NoSelection);

    addButton(1, "Refresh", QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\refresh-24.png"), &MpFileTreeview::refreshRow);
    addButton(2, "Remove", QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\remove-24.png"), &MpFileTreeview::removeRow);
   
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
        button->setMaximumWidth(24);
        setIndexWidget(child, button);
        connect(button, &QPushButton::released, this, slotName);
    }
}

void MpFileTreeview::refreshRow()
{
}

void MpFileTreeview::removeRow()
{
    const QModelIndex index = this->selectionModel()->currentIndex();
    this->model()->removeRow(index.row(), index.parent());
}

