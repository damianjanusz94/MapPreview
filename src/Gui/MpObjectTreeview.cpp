#include "MpObjectTreeview.h"

#include <QtWidgets\QHeaderView>

MpObjectTreeview::MpObjectTreeview(QWidget* parent) : QTreeView(parent)
{
    objectTreeModel = std::make_unique<ObjectTreeModel>("ddd \nfff", this);

    setModel(objectTreeModel.get());
    setHeaderHidden(true);
    header()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    header()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    header()->setStretchLastSection(false);
    setFocusPolicy(Qt::FocusPolicy::NoFocus);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setStyleSheet("selection-background-color: rgb(240, 240, 240);selection-color: black");

}
