#include "MpFileAddWindow.h"

#include <QtWidgets/QBoxLayout>

MpFileAddWindow::MpFileAddWindow(QWidget* parent) : QDialog(parent)
{
	setObjectName("AddFileWindow");
	setWindowTitle("Add file");
	setModal(true);
	setMinimumSize(400, 400);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(buttonBox, 0, Qt::AlignBottom | Qt::AlignRight);

	setLayout(mainLayout);
}
