#include "MpFileTreeview.h"

#include <QtCore\QFile>
#include <QtCore\QDir>

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

void MpFileTreeview::addColorPickers(const QModelIndex& index, std::shared_ptr<GeoLayer> geoLayer)
{
    auto geoChildren = fileTreeModel->getItemChildren(index, EXTENSION_COLUMN);
    if (geoChildren.count() != 3)
        return;

    QColor colorPoint = geoLayer->getColor(GeoType::POINT);
    QColor colorLine = geoLayer->getColor(GeoType::LINE);
    QColor colorPolygon = geoLayer->getColor(GeoType::POLYGON);

    auto buttonPoint = new QPushButton();
    auto buttonLine = new QPushButton();
    auto buttonPolygon = new QPushButton();

    buttonPoint->setStyleSheet("background-color : " + colorPoint.name());
    buttonLine->setStyleSheet("background-color : " + colorLine.name());
    buttonPolygon->setStyleSheet("background-color : " + colorPolygon.name());

    setIndexWidget(geoChildren[0], buttonPoint);
    setIndexWidget(geoChildren[1], buttonLine);
    setIndexWidget(geoChildren[2], buttonPolygon);

    connect(buttonPoint, &QPushButton::released, this, [this, buttonPoint, geoLayer] { changeColor(buttonPoint, geoLayer, GeoType::POINT); });
    connect(buttonLine, &QPushButton::released, this, [this, buttonLine, geoLayer] { changeColor(buttonLine, geoLayer, GeoType::LINE); });
    connect(buttonPolygon, &QPushButton::released, this, [this, buttonPolygon, geoLayer] { changeColor(buttonPolygon, geoLayer, GeoType::POLYGON); });

    geoLayer->setColorButtonConnection(buttonPoint, buttonLine, buttonPolygon);
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

void MpFileTreeview::changeColor(QPushButton* button, std::shared_ptr<GeoLayer> geo_layer, GeoType geo_type)
{
    QColor oldColor = button->palette().window().color();
    QColor newColor = QColorDialog::getColor(oldColor, nullptr, "Pick a color");
    if (!newColor.isValid())
    {
        return;
    }

    if (newColor != oldColor)
    {
        geo_layer->setColor(newColor, geo_type);
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

    fileTreeModel->setColorsGeoLayer(index, newColor);
}

void MpFileTreeview::addFileItem(const QString& filePath, std::shared_ptr<GeoLayer> geoLayer)
{
    const QModelIndex& lastIndex = fileTreeModel->getLastRootChildren(TEXT_COLUMN);

    if (!fileTreeModel->insertMainRow(lastIndex.row() + 1, geoLayer, lastIndex.parent()))
        return;

    addButtonExtension(fileTreeModel->getLastRootChildren(EXTENSION_COLUMN), FileHelper::getFileExtension(filePath));
    addButton(fileTreeModel->getLastRootChildren(REFRESH_COLUMN), "Refresh", QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\refresh-24.png"), &MpFileTreeview::refreshRow);
    addButton(fileTreeModel->getLastRootChildren(REMOVE_COLUMN), "Remove", QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\remove-24.png"), &MpFileTreeview::removeRow);
    addColorPickers(fileTreeModel->getLastRootChildren(TEXT_COLUMN), geoLayer);
}