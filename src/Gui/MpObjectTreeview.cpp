#include "MpObjectTreeview.h"

#include <QtCore\QRandomGenerator>
#include <QtWidgets\QHeaderView>
#include <QtWidgets\QColorDialog>

#include "../Models/ColorDelegate.h"

using namespace Enums;

MpObjectTreeview::MpObjectTreeview(std::shared_ptr<ObjectTreeModel> object_model, QWidget* parent) : QTreeView(parent), objectTreeModel(object_model)
{
    setItemDelegate(new ColorDelegate());
    setModel(objectTreeModel.get());
    setHeaderHidden(true);
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header()->setStretchLastSection(false);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    setEditTriggers(QAbstractItemView::CurrentChanged);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setStyleSheet("selection-background-color: rgb(240, 240, 240);selection-color: black");
}

void MpObjectTreeview::addFileItem(const QString& filePath, std::shared_ptr<GeoLayer> geoLayer)
{
    if (!objectTreeModel->insertFileChild(filePath, geoLayer))
        return;
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

    objectTreeModel->setColorsGeoLayer(index, newColor);
}

void MpObjectTreeview::connectButtonWithSelection(QPushButton* button)
{
    if (button == nullptr)
        return;

    connect(this->selectionModel(), &QItemSelectionModel::selectionChanged, this, [this, button] { onSelectionChanged(button); });
}

void MpObjectTreeview::onSelectionChanged(QPushButton* button)
{
    if (button == nullptr)
        return;


    if (!this->selectionModel()->hasSelection())
    {
        button->setEnabled(false);
        return;
    }

    const QModelIndex index = this->selectionModel()->currentIndex();
    if (objectTreeModel->isMainItem(index))
    {
        button->setEnabled(true);
    }
    else
    {
        button->setEnabled(false);
    }

}
