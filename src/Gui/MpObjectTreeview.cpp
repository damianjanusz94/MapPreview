#include "MpObjectTreeview.h"

#include <QtCore\QRandomGenerator>
#include <QtWidgets\QHeaderView>
#include <QtWidgets\QColorDialog>

#include "../Models/GeoLayer.h"

MpObjectTreeview::MpObjectTreeview(std::shared_ptr<ObjectTreeModel> object_model, QWidget* parent) : QTreeView(parent), objectTreeModel(object_model)
{
    setModel(objectTreeModel.get());
    setHeaderHidden(true);
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header()->setStretchLastSection(false);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setStyleSheet("selection-background-color: rgb(240, 240, 240);selection-color: black");
}

void MpObjectTreeview::addFileItem(const QString& filePath, std::shared_ptr<GeoLayer> geoLayer)
{
    if (!objectTreeModel->insertFileChild(filePath, geoLayer))
        return;

    addColorPickers(objectTreeModel->getLastGeoFiles(EXTENSION_COLUMN), geoLayer);
}

void MpObjectTreeview::addColorPickers(const QList<QModelIndex> indexList, std::shared_ptr<GeoLayer> geoLayer)
{
    for (const auto& child : indexList)
    {
        auto button = new QPushButton();
        QColor color = geoLayer->getColor(static_cast<GeoType>(child.parent().row()));
        button->setStyleSheet("background-color : " + color.name());
        setIndexWidget(child, button);
        connect(button, &QPushButton::released, this, [this, button] { changeColor(button); });
    }
}

void MpObjectTreeview::changeColor(QPushButton* button)
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

void MpObjectTreeview::setColorForItems()
{
    if (!this->selectionModel()->hasSelection())
    {
        return;
    }

    const QModelIndex index = this->selectionModel()->currentIndex();
    if (!objectTreeModel->isMainItem(index))
    {
        return;
    }

    QColor newColor = QColorDialog::getColor(Qt::white, nullptr, "Pick a color");
    if (!newColor.isValid())
    {
        return;
    }

    auto childItems = objectTreeModel->getItemChildren(index, EXTENSION_COLUMN);
    for (const auto& child : childItems)
    {
        QPushButton* button = static_cast<QPushButton*>(indexWidget(child));
        button->setStyleSheet("background-color : " + newColor.name());
    }
}