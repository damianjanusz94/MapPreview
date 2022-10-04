#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QPushButton>
#include <QtCore\QDir>

#include "Settings\MpSettingsDialog.h"

class MpMainToolbar : public QToolBar
{
	Q_OBJECT

	QPushButton* settingsBtn;
	std::unique_ptr<MpSettingsDialog> settingsDialog;

public:
	explicit MpMainToolbar(QWidget* parent);

private slots:
	void settingsDialogOpen();
};

