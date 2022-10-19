#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QPushButton>
#include <QtCore\QDir>

#include "MpFileTreeview.h"
#include "MpFileAddWindow.h"
#include "../NppPlugin/NppProxy.h"

class MpFileTvToolbar : public QToolBar
{
	Q_OBJECT

	std::weak_ptr<MpFileTreeview> fileTreeview;
	std::unique_ptr<MpFileAddWindow> fileAddWindow;
	std::shared_ptr<NppProxy> nppProxy;
	std::shared_ptr<FileTreeModel> fileTreeModel;

	QPushButton* refreshAllBtn;
	QPushButton* removeAllBtn;
	QPushButton* addBtn;
	QPushButton* upBtn;
	QPushButton* downBtn;
	QPushButton* upMaxBtn;
	QPushButton* downMaxBtn;

	void setupRefreshAllBtn();
	void setupRemoveAllBtn();
	void setupAddBtn();
	void setupUpBtn();
	void setupDownBtn();
	void setupUpMaxBtn();
	void setupDownMaxBtn();

private slots:
	void showFileDialog();

public:
	explicit MpFileTvToolbar(std::shared_ptr<NppProxy> pNppProxy, std::weak_ptr<MpFileTreeview> fileTv, 
							 std::shared_ptr<FileTreeModel> fileModel, QWidget* parent = nullptr);
};
