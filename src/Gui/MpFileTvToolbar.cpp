#include "MpFileTvToolbar.h"

#include<QtWidgets\QLayout>
#include<QtWidgets\QMessageBox>

MpFileTvToolbar::MpFileTvToolbar(std::shared_ptr<NppProxy> pNppProxy, std::weak_ptr<MpFileTreeview> fileTv,
                                 std::shared_ptr<FileTreeModel> fileModel, QWidget* parent)
                                 : fileTreeview(fileTv), QToolBar(parent), fileTreeModel(fileModel), nppProxy(pNppProxy)
{
    fileAddWindow = std::make_unique<MpFileAddWindow>(nppProxy);
    setWindowTitle("FileTvToolbar");
    setObjectName("File toolbar");
    this->layout()->setContentsMargins(0, 0, 0, 0);

    setupAddBtn();
    setupRefreshAllBtn();
    setupRemoveAllBtn();
    setupUpBtn();
    setupDownBtn();
    setupUpMaxBtn();
    setupDownMaxBtn();
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

    connect(addBtn, &QPushButton::released, this, &MpFileTvToolbar::showFileDialog);
}

void MpFileTvToolbar::setupUpBtn()
{
    upBtn = new QPushButton();
    upBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\up-24.png"));
    upBtn->setFlat(true);
    upBtn->setToolTip("Move up");
    addWidget(upBtn);
    connect(upBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::moveUp);
}

void MpFileTvToolbar::setupDownBtn()
{
    downBtn = new QPushButton();
    downBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\down-24.png"));
    downBtn->setFlat(true);
    downBtn->setToolTip("Move down");
    addWidget(downBtn);
    connect(downBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::moveDown);
}

void MpFileTvToolbar::setupUpMaxBtn()
{
    upMaxBtn = new QPushButton();
    upMaxBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\updouble-48.png"));
    upMaxBtn->setFlat(true);
    upMaxBtn->setToolTip("Move to first");
    addWidget(upMaxBtn);
    connect(upMaxBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::moveToFirst);
}

void MpFileTvToolbar::setupDownMaxBtn()
{
    downMaxBtn = new QPushButton();
    downMaxBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\downdouble-48.png"));
    downMaxBtn->setFlat(true);
    downMaxBtn->setToolTip("Move to last");
    addWidget(downMaxBtn);
    connect(downMaxBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::moveToLast);
}

void MpFileTvToolbar::showFileDialog()
{
    fileAddWindow->fillListView(fileTreeModel->getAllFilePaths());

    if (fileAddWindow->isListEmpty())
    {
        QMessageBox infoMsg;
        infoMsg.setWindowTitle(QString("Map Preview"));
        infoMsg.setText(QString("All of available files are already on list"));
        infoMsg.setIcon(QMessageBox::Information);
        infoMsg.exec();
        return;
    }

    if (fileAddWindow->exec() == QDialog::Accepted)
    {
        fileTreeview.lock()->addFileItems(fileAddWindow->getSelectedFiles());
    }
}