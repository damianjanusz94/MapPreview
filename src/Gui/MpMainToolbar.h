#pragma once

#include <QtWidgets\QToolBar>
#include <QtWidgets\QPushButton>
#include <QtCore\QDir>

#include "Settings\MpSettingsDialog.h"
#include "MessageWindow.h"

class MpMainToolbar : public QToolBar
{
	Q_OBJECT

	QPushButton* settingsBtn;
	QPushButton* refreshBtn;
	std::unique_ptr<MpSettingsDialog> settingsDialog;
	std::shared_ptr<MessageWindow> msgWindow;

public:
	explicit MpMainToolbar(QWidget* parent, std::shared_ptr<MessageWindow> messageWindow);

private slots:
	void settingsDialogOpen();
};

