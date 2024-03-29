#include "ObjectTvToolbar.h"

#include<QtWidgets\QLayout>

ObjectTvToolbar::ObjectTvToolbar(std::weak_ptr<MpObjectTreeview> objectTv, std::shared_ptr<MessageWindow> messageWindow, QWidget* parent) : QToolBar(parent), objectTreeview(objectTv), msgWindow(messageWindow)
{
    setWindowTitle("ObjectTvToolbar");
    setObjectName("Object toolbar");
    this->layout()->setContentsMargins(0, 0, 0, 0);

    setupColorBtn();
}

void ObjectTvToolbar::setupColorBtn()
{
    colorBtn = new QPushButton();
    colorBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\color-48.png"));
    colorBtn->setFlat(true);
    colorBtn->setEnabled(false);
    colorBtn->setToolTip("Set one color for object");
    addWidget(colorBtn);
    connect(colorBtn, &QPushButton::released, objectTreeview.lock().get(), &MpObjectTreeview::setColorForItems);
    objectTreeview.lock()->connectButtonWithSelection(colorBtn);
}

