#include "MpSettingsDialog.h"
#include "MpGeneralTab.h"
#include "MpTabStyle.h"

#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QTabBar>

MpSettingsDialog::MpSettingsDialog(QWidget* parent) : QDialog(parent)
{
	setObjectName("MapPreviewSettings");
	setWindowTitle("Map Preview Settings");
	setModal(true);
	setMinimumSize(800, 400);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    
	tabWidget = new QTabWidget;
	tabWidget->tabBar()->setStyle(new MpTabStyle());
	tabWidget->addTab(new MpGeneralTab(), tr("General"));
	tabWidget->setTabPosition(QTabWidget::West);

	mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox, 0, Qt::AlignBottom | Qt::AlignRight);

    setLayout(mainLayout);
}
