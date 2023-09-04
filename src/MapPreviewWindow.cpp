#include "MapPreviewWindow.h"
#include "MapPreviewResources.h"
#include <QtWidgets\QGridLayout>
#include <QtWidgets/qpushbutton.h>
#include "../MapPreview/include/gdal/gdal.h"

MapPreviewWindow::MapPreviewWindow(HANDLE hModule) : DockingDlgInterface(IDD_DIALOG_CONSOLE), hModule(hModule)
{
	ownApplication = QMfcApp::pluginInstance(hModule);
	QApplication::setStyle("Fusion");
	GDALAllRegister();
}

MapPreviewWindow::~MapPreviewWindow()
{
}

void MapPreviewWindow::Display(bool toShow) const
{
	DockingDlgInterface::display(toShow);
}

void MapPreviewWindow::Initialize(NppData nppData)
{
	InitializeDialog(nppData);
	InitializeResources(nppData);
	InitializeDependencies();
}

void MapPreviewWindow::InitializeDialog(NppData nppData)
{
	init((HINSTANCE)hModule, NULL);
	setParent(nppData._nppHandle);
	tTbData	data = { 0 };

	if (!isCreated())
	{
		create(&data);

		data.uMask = DWS_DF_CONT_BOTTOM;
		data.pszName = _T("Map Preview");
		data.pszModuleName = getPluginFileName();
		data.dlgID = IDD_DIALOG_CONSOLE;
		::SendMessage(nppData._nppHandle, NPPM_DMMREGASDCKDLG, 0, (LPARAM)&data);
	}

	nppProxy = std::make_shared<NppProxy>(nppData);

	qtMainWidget = std::make_unique<QWinWidget>(_hSelf);
	winId = (HWND)qtMainWidget->winId();

	mpMainWindow = std::make_shared<MainWindow>(nppProxy);
	mpMainWindow->setWindowFlag(Qt::Widget);

	QVBoxLayout hbox;
	hbox.setSpacing(1);
	hbox.addWidget(mpMainWindow.get(), Qt::AlignCenter);
	hbox.setContentsMargins(0, 0, 0, 0);

	qtMainWidget->setLayout(&hbox);
	qtMainWidget->move(0, 0);
	qtMainWidget->show();

	ready = true;
}

void MapPreviewWindow::InitializeResources(NppData nppData)
{
	nppData;
}

void MapPreviewWindow::InitializeDependencies()
{
}


INT_PTR CALLBACK MapPreviewWindow::run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	INT_PTR handleResult = DockingDlgInterface::run_dlgProc(message, wParam, lParam);

	switch (message)
	{
		case WM_NOTIFY:
		case WM_SIZE:
			if (ready)
				OnSize(_hSelf);
			return TRUE;
		case WM_DESTROY:
			OnDestroy();
		default:
			return handleResult;
	}
}

void MapPreviewWindow::OnSize(HWND hDlg) 
{
	if (hDlg == nullptr)
		return;

	RECT rect;
	GetClientRect(hDlg, &rect);

	qtMainWidget->resize(QSize(abs(rect.right-rect.left), abs(rect.top-rect.bottom)));
	mpMainWindow->resize(QSize(abs(rect.right-rect.left), abs(rect.top-rect.bottom)));
}

void MapPreviewWindow::OnDestroy()
{
	if (mpMainWindow.get())
	{
		mpMainWindow->close();
	}
}
