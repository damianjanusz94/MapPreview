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
	QPushButton* refreshAllBtn;
	QPushButton* removeAllBtn;
	QPushButton* addBtn;

	void setupRefreshAllBtn();
	void setupRemoveAllBtn();
	void setupAddBtn();

private slots:
	void addFileDialog();

public:
	explicit MpFileTvToolbar(std::shared_ptr<NppProxy> pNppProxy, std::weak_ptr<MpFileTreeview> fileTv, QWidget* parent = nullptr);
};

