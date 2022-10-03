#include "MpSettingsDialog.h"
#include <QtWidgets/QBoxLayout>

MpSettingsDialog::MpSettingsDialog(QWidget* parent) : QDialog(parent)
{
	setObjectName("MapPreviewSettings");
	setWindowTitle("Map Preview Settings");
	setModal(true);

	saveBtn = new QPushButton("Save");
	cancelBtn = new QPushButton("Cancel");

	QVBoxLayout vertLayout;
	vertLayout.setSpacing(2);
	vertLayout.addWidget(saveBtn);
	vertLayout.addWidget(cancelBtn);

	QHBoxLayout horiLayout;
	horiLayout.setSpacing(2);
	

	vertLayout.addLayout(&horiLayout);
	
	setLayout(&vertLayout);
}
