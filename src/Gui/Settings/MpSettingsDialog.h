#pragma once

#include <QtWidgets\QDialog>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QDialogButtonBox>
#include <QtWidgets\QTabWidget>

#include "MpGeneralTab.h"
#include "MpViewTab.h"
#include "../MessageWindow.h"


class MpSettingsDialog : public QDialog
{
	QDialogButtonBox* buttonBox;
	QTabWidget* tabWidget;

	std::unique_ptr<MpGeneralTab> generalTab;
	std::unique_ptr<MpViewTab> viewTab;
	std::shared_ptr<MessageWindow> msgWindow;;

public:
	explicit MpSettingsDialog(std::shared_ptr<MessageWindow> messageWindow, QWidget* parent = nullptr);
};
