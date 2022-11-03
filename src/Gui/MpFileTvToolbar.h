#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QPushButton>
#include <QtCore\QDir>

#include "MpFileTreeview.h"
#include "MpFileAddWindow.h"
#include "MpObjectTreeview.h"
#include "../NppPlugin/NppProxy.h"

class MpFileTvToolbar : public QToolBar
{
	Q_OBJECT

	std::weak_ptr<MpFileTreeview> fileTreeview;
	std::unique_ptr<MpFileAddWindow> fileAddWindow;
	std::shared_ptr<FileTreeModel> fileTreeModel;
	std::weak_ptr<MpObjectTreeview> objectTreeview;
	std::shared_ptr<NppProxy> nppProxy;
	std::shared_ptr<NppFilesList> nppFileList;

	QPushButton* refreshAllBtn;
	QPushButton* removeAllBtn;
	QPushButton* addBtn;
	QPushButton* upBtn;
	QPushButton* downBtn;
	QPushButton* upMaxBtn;
	QPushButton* downMaxBtn;
	QPushButton* colorBtn;

	void setupRefreshAllBtn();
	void setupRemoveAllBtn();
	void setupAddBtn();
	void setupUpBtn();
	void setupDownBtn();
	void setupUpMaxBtn();
	void setupDownMaxBtn();
	void setupColorBtn();

private slots:
	void showFileDialog();

public:
	explicit MpFileTvToolbar(std::shared_ptr<NppProxy> pNppProxy, std::weak_ptr<MpFileTreeview> fileTv, 
							 std::shared_ptr<FileTreeModel> fileModel, std::weak_ptr<MpObjectTreeview> objectTv, QWidget* parent = nullptr);
};

