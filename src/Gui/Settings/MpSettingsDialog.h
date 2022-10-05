#pragma once

#include <QtWidgets\QDialog>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QDialogButtonBox>
#include <QtWidgets\QTabWidget>

#include "MpGeneralTab.h"
#include "MpViewTab.h"

class MpSettingsDialog : public QDialog
{
	QDialogButtonBox* buttonBox;
	QTabWidget* tabWidget;

	std::unique_ptr<MpGeneralTab> generalTab;
	std::unique_ptr<MpViewTab> viewTab;

public:
	explicit MpSettingsDialog(QWidget* parent = nullptr);
};
