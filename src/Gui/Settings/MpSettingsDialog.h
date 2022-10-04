#pragma once

#include <QtWidgets\QDialog>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QDialogButtonBox>
#include <QtWidgets\QTabWidget>

class MpSettingsDialog : public QDialog
{
	QDialogButtonBox* buttonBox;
	QTabWidget* tabWidget;

public:
	explicit MpSettingsDialog(QWidget* parent = nullptr);
};
