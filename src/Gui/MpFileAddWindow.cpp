#include "MpFileAddWindow.h"
#include "../Enums/GeoExtType.h"

#include <QtCore\QDir>

using namespace Enums;

MpFileAddWindow::MpFileAddWindow(std::shared_ptr<NppProxy> pNppProxy, QWidget* parent) : QDialog(parent), nppProxy(pNppProxy)
{
	nppFileList = std::make_unique<NppFilesList>(nppProxy);
	setObjectName("AddFileWindow");
	setWindowTitle("Add files");
	setModal(true);
	setMinimumSize(400, 400);

	mainLayout = new QVBoxLayout;
	
	setupListView();
	setupButtons();
	
	setLayout(mainLayout);
}

void MpFileAddWindow::setupButtons()
{
	buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
		| QDialogButtonBox::Cancel);

	connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
	connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

	selectAllBtn = new QPushButton();
	selectAllBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\tickall-24.png"));
	selectAllBtn->setFlat(true);
	selectAllBtn->setToolTip("Select all");

	unselectAllBtn = new QPushButton();
	unselectAllBtn->setIcon(QIcon(QDir::currentPath() + "\\plugins\\MapPreview\\icons\\untickall-24.png"));
	unselectAllBtn->setFlat(true);
	unselectAllBtn->setToolTip("Unselect all");

	connect(selectAllBtn, &QPushButton::released, this, &MpFileAddWindow::selectAllFiles);
	connect(unselectAllBtn, &QPushButton::released, this, &MpFileAddWindow::unselectAllFiles);

	QHBoxLayout* hLayout = new QHBoxLayout();
	hLayout->addWidget(selectAllBtn, 0, Qt::AlignLeft);
	hLayout->addWidget(unselectAllBtn, 0, Qt::AlignLeft);
	hLayout->addStretch();
	hLayout->addWidget(buttonBox, 0, Qt::AlignRight);

	mainLayout->addLayout(hLayout);
}

void MpFileAddWindow::setupListView()
{
	listWidget = new QListWidget();

	listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
	mainLayout->addWidget(listWidget);
}

void MpFileAddWindow::fillListView(QStringList currentFiles)
{
	listWidget->clear();

	auto nppFiles = nppFileList->readNppFilesInfo();
	for (const auto& file : nppFiles)
	{
		if (!file.extension.isEmpty() && !GeoExtType::isGeoExtType(file.extension))
			continue;

		QString fileName = file.currentPath.isEmpty() ? file.fileName : file.currentPath;

		if (currentFiles.contains(fileName))
			continue;

		auto item = new QListWidgetItem(file.fileName);
		QVariant dataItem(fileName);
		item->setData(Qt::UserRole, dataItem);
		listWidget->addItem(item);
	}
}

void MpFileAddWindow::unselectAllFiles()
{
	listWidget->clearSelection();
}

void MpFileAddWindow::selectAllFiles()
{
	listWidget->selectAll();
}

QStringList MpFileAddWindow::getSelectedFiles()
{
	QStringList selectedNppFiles;

	auto selectedItems = listWidget->selectedItems();
	for (auto item : selectedItems)
	{
		selectedNppFiles.append(item->data(Qt::UserRole).toString());
	}

	nppFileList->readNppFiles();
	
	return selectedNppFiles;
}