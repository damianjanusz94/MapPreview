#include "MpFileTvToolbar.h"

#include<QtWidgets\QLayout>

MpFileTvToolbar::MpFileTvToolbar(std::shared_ptr<NppProxy> pNppProxy, std::weak_ptr<MpFileTreeview> fileTv, QWidget* parent) 
    : fileTreeview(fileTv), QToolBar(parent), nppProxy(pNppProxy)
{
    fileAddWindow = std::make_unique<MpFileAddWindow>(nppProxy);
    setWindowTitle("FileTvToolbar");
    setObjectName("File toolbar");
    this->layout()->setContentsMargins(0, 0, 0, 0);

    setupAddBtn();
    setupRefreshAllBtn();
    setupRemoveAllBtn();
}

void MpFileTvToolbar::setupRefreshAllBtn()
{
    refreshAllBtn = new QPushButton();
    refreshAllBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\refresh-24.png"));
    refreshAllBtn->setFlat(true);
    refreshAllBtn->setToolTip("Refresh all");
    addWidget(refreshAllBtn);
}

void MpFileTvToolbar::setupRemoveAllBtn()
{
    removeAllBtn = new QPushButton();
    removeAllBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\remove-24.png"));
    removeAllBtn->setFlat(true);
    removeAllBtn->setToolTip("Remove all");
    addWidget(removeAllBtn);

    connect(removeAllBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::removeAll);
}

void MpFileTvToolbar::setupAddBtn()
{
    addBtn = new QPushButton();
    addBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\add-24.png"));
    addBtn->setFlat(true);
    addBtn->setToolTip("Add file to list");
    addWidget(addBtn);

    connect(addBtn, &QPushButton::released, this, &MpFileTvToolbar::addFileDialog);
}

void MpFileTvToolbar::addFileDialog()
{
    fileAddWindow->showWindow();
}