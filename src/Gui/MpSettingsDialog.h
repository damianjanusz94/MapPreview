#pragma once

#include <QtWidgets\QDialog>
#include <QtWidgets\QPushButton>

class MpSettingsDialog : public QDialog
{
	QPushButton* saveBtn;
	QPushButton* cancelBtn;

public:
	explicit MpSettingsDialog(QWidget* parent = nullptr);
};
