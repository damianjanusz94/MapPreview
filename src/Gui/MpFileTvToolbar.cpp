#include "MpFileTvToolbar.h"

#include<QtWidgets\QLayout>
#include<QtWidgets\QMessageBox>

#include "../Models/GeoLayer.h"

MpFileTvToolbar::MpFileTvToolbar(std::shared_ptr<NppProxy> pNppProxy, std::weak_ptr<MpFileTreeview> fileTv,
                                 std::shared_ptr<FileTreeModel> fileModel, std::weak_ptr<MpObjectTreeview> objectTv, QWidget* parent)
                                 : fileTreeview(fileTv), QToolBar(parent), fileTreeModel(fileModel), objectTreeview(objectTv), nppProxy(pNppProxy)
{
    nppFileList = std::make_unique<NppFilesList>(nppProxy);
    fileAddWindow = std::make_unique<MpFileAddWindow>(nppFileList);
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
    setupColorBtn();
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
    upBtn->setEnabled(false);
    upBtn->setToolTip("Move up");
    addWidget(upBtn);
    connect(upBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::moveUp);
    fileTreeview.lock()->connectButtonWithSelection(upBtn);
}

void MpFileTvToolbar::setupDownBtn()
{
    downBtn = new QPushButton();
    downBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\down-24.png"));
    downBtn->setFlat(true);
    downBtn->setEnabled(false);
    downBtn->setToolTip("Move down");
    addWidget(downBtn);
    connect(downBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::moveDown);
    fileTreeview.lock()->connectButtonWithSelection(downBtn);
}

void MpFileTvToolbar::setupUpMaxBtn()
{
    upMaxBtn = new QPushButton();
    upMaxBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\updouble-48.png"));
    upMaxBtn->setFlat(true);
    upMaxBtn->setEnabled(false);
    upMaxBtn->setToolTip("Move to first");
    addWidget(upMaxBtn);
    connect(upMaxBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::moveToFirst);
    fileTreeview.lock()->connectButtonWithSelection(upMaxBtn);
}

void MpFileTvToolbar::setupDownMaxBtn()
{
    downMaxBtn = new QPushButton();
    downMaxBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\downdouble-48.png"));
    downMaxBtn->setFlat(true);
    downMaxBtn->setEnabled(false);
    downMaxBtn->setToolTip("Move to last");
    addWidget(downMaxBtn);
    connect(downMaxBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::moveToLast);
    fileTreeview.lock()->connectButtonWithSelection(downMaxBtn);
}

void MpFileTvToolbar::setupColorBtn()
{
    colorBtn = new QPushButton();
    colorBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\color-48.png"));
    colorBtn->setFlat(true);
    colorBtn->setEnabled(false);
    colorBtn->setToolTip("Set one color for file");
    addWidget(colorBtn);
    connect(colorBtn, &QPushButton::released, fileTreeview.lock().get(), &MpFileTreeview::setColorForItems);
    fileTreeview.lock()->connectButtonWithSelection(colorBtn);
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
        const QStringList& selectedFiles = fileAddWindow->getSelectedFiles();

        for (const auto& file : selectedFiles)
        {
            const QString text = nppFileList->readDocText(file);
            auto geoLayerPtr = std::make_shared<GeoLayer>(file, text);

            fileTreeview.lock()->addFileItem(file, geoLayerPtr);
            objectTreeview.lock()->addFileItem(file, geoLayerPtr);
        }
    }
}