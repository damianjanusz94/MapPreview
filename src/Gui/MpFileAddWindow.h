#pragma once

#include <QtWidgets\QDialog>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QDialogButtonBox>

class MpFileAddWindow : public QDialog
{
	QDialogButtonBox* buttonBox;

public:
	explicit MpFileAddWindow(QWidget* parent = nullptr);
};

