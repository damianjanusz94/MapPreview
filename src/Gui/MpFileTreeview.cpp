#include "MpFileTreeview.h"

#include <QtCore\QFile>
#include <QtCore\QDir>
#include <QtCore\QRandomGenerator>
#include <QtWidgets\QColorDialog>
#include <QtWidgets\QHeaderView>

#include "../Enums/GeoExtType.h"
#include "../Models/FileHelper.h"

using namespace Enums;

MpFileTreeview::MpFileTreeview(std::shared_ptr<FileTreeModel> fileModel, QWidget* parent) : QTreeView(parent), fileTreeModel(fileModel)
{
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
}

void MpFileTreeview::addButton(const QModelIndex& index, QString tooltip, QIcon icon, void(MpFileTreeview::* slotName)())
{
    auto button = new QPushButton();
    button->setIcon(icon);
    button->setFlat(true);
    button->setToolTip(tooltip);
    setIndexWidget(index, button);
    connect(button, &QPushButton::released, this, slotName);
}

void MpFileTreeview::addButtonExtension(const QModelIndex& index, const QString& fileExtension)
{
    const QString& extType = GeoExtType::getGeoExtStringOrUnknown(fileExtension);
    auto button = new QPushButton(extType);
    button->setFlat(true);
    button->setToolTip("File type");
    button->setEnabled(false);
    if (extType == "unknown")
    {
        button->setEnabled(true);
        setupMenuExtension(button);
    }
    setIndexWidget(index, button);
}

void MpFileTreeview::addColorPickers(const QModelIndex& index)
{
    auto geoChildren = fileTreeModel->getItemChildren(index, 1);
    for (const auto& child : geoChildren)
    {
        auto button = new QPushButton();
        QColor color(QRandomGenerator::global()->bounded(0, 255),
                     QRandomGenerator::global()->bounded(0, 255), 
                     QRandomGenerator::global()->bounded(0, 255));
        button->setStyleSheet("background-color : " + color.name());
        setIndexWidget(child, button);
        connect(button, &QPushButton::released, this, [this, button] { changeColor(button); });
    }
}

void MpFileTreeview::setupMenuExtension(QPushButton* button)
{
    auto menuExtension = new QMenu();

    QAction* unknownAction = new QAction(GeoExtType::GetGeoExtTypeString(GeoExtType::ExtType::unknown), button);
    QAction* geojsonAction = new QAction(GeoExtType::GetGeoExtTypeString(GeoExtType::ExtType::GEOJSON), button);
    QAction* wkbAction = new QAction(GeoExtType::GetGeoExtTypeString(GeoExtType::ExtType::WKB), button);
    QAction* wktAction = new QAction(GeoExtType::GetGeoExtTypeString(GeoExtType::ExtType::WKT), button);
    
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

void MpFileTreeview::changeColor(QPushButton* button)
{
    QColor oldColor = button->palette().window().color();
    QColor newColor = QColorDialog::getColor(oldColor, nullptr, "Pick a color");
    if (!newColor.isValid())
    {
        return;
    }

    if (newColor != oldColor)
    {
        button->setStyleSheet("background-color : " + newColor.name());
    }
}

void MpFileTreeview::setColorForItems()
{
    if (!this->selectionModel()->hasSelection())
    {
        return;
    }

    const QModelIndex index = this->selectionModel()->currentIndex();
    if (!fileTreeModel->isMainItem(index))
    {
        return;
    }

    QColor newColor = QColorDialog::getColor(Qt::white, nullptr, "Pick a color");
    if (!newColor.isValid())
    {
        return;
    }

    auto childItems = fileTreeModel->getItemChildren(index, 1);
    for (const auto& child : childItems)
    {
        QPushButton* button = static_cast<QPushButton*>(indexWidget(child));
        button->setStyleSheet("background-color : " + newColor.name());
    }
}

void MpFileTreeview::addFileItems(const QStringList& filePaths)
{
    for (const auto& file : filePaths)
    {
        addFileItem(file);
    }
}

void MpFileTreeview::addFileItem(const QString& filePath)
{
    const QModelIndex& lastIndex = fileTreeModel->getLastRootChildren(TEXT_COLUMN);

    if (!fileTreeModel->insertMainRow(lastIndex.row() + 1, filePath, lastIndex.parent()))
        return;

    addButtonExtension(fileTreeModel->getLastRootChildren(EXTENSION_COLUMN), FileHelper::getFileExtension(filePath));
    addButton(fileTreeModel->getLastRootChildren(REFRESH_COLUMN), "Refresh", QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\refresh-24.png"), &MpFileTreeview::refreshRow);
    addButton(fileTreeModel->getLastRootChildren(REMOVE_COLUMN), "Remove", QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\remove-24.png"), &MpFileTreeview::removeRow);
    addColorPickers(fileTreeModel->getLastRootChildren(TEXT_COLUMN));
}