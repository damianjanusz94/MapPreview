#include "MpObjectTreeview.h"

#include <QtWidgets\QHeaderView>

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

void MpObjectTreeview::addFileItems(const QStringList& filePaths)
{
    for (const auto& file : filePaths)
    {
        addFileItem(file);
    }
}

void MpObjectTreeview::addFileItem(const QString& filePath)
{
    if (!objectTreeModel->insertFileChild(filePath))
        return;

}