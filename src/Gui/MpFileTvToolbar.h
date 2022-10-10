#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QPushButton>
#include <QtCore\QDir>

#include "MpFileTreeview.h"

class MpFileTvToolbar : public QToolBar
{
	std::weak_ptr<MpFileTreeview> fileTreeview;
	QPushButton* refreshAllBtn;
	QPushButton* removeAllBtn;

	void setupRefreshAllBtn();
	void setupRemoveAllBtn();

public:
	explicit MpFileTvToolbar(std::weak_ptr<MpFileTreeview> fileTv, QWidget* parent = nullptr);

};

