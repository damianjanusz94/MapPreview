#include "MpSettingsDialog.h"
#include "MpTabStyle.h"

#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QTabBar>

MpSettingsDialog::MpSettingsDialog(QWidget* parent) : QDialog(parent)
{
	generalTab = std::make_unique<MpGeneralTab>();
	viewTab = std::make_unique<MpViewTab>();

	setObjectName("MapPreviewSettings");
	setWindowTitle("Map Preview Settings");
	setModal(true);
	setMinimumSize(800, 400);

	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    
	tabWidget = new QTabWidget;
	tabWidget->tabBar()->setStyle(new MpTabStyle());
	tabWidget->setTabPosition(QTabWidget::West);
	tabWidget->addTab(generalTab.get(), tr("General"));
	tabWidget->addTab(viewTab.get(), tr("View"));

    QVBoxLayout* mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabWidget);
    mainLayout->addWidget(buttonBox, 0, Qt::AlignBottom | Qt::AlignRight);

    setLayout(mainLayout);
}
