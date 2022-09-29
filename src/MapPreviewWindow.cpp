#include "MapPreviewWindow.h"
#include "MapPreviewResources.h"
#include <QtWidgets\QGridLayout>
#include <QtWidgets/qpushbutton.h>

MapPreviewWindow::MapPreviewWindow(HANDLE hModule) : DockingDlgInterface(IDD_DIALOG_CONSOLE), hModule(hModule)
{
	ownApplication = QMfcApp::pluginInstance(hModule);
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

	qtMainWidget = std::make_unique<QWinWidget>(_hSelf);
	winId = (HWND)qtMainWidget->winId();
	QVBoxLayout hbox(qtMainWidget.get());
	hbox.setSpacing(1);

	mpMainWindow = std::make_shared<MPMainWindow>();
	mpMainWindow->setWindowFlag(Qt::SubWindow);

	hbox.addWidget(mpMainWindow.get());

	qtMainWidget->resize(1000, 1000);
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

	//MoveWindow(windowGL->getHandle(), rect.left, rect.top, rect.right, rect.bottom, TRUE);
	//InvalidateRect(windowGL->getHandle(), NULL, TRUE);
	//UpdateWindow(windowGL->getHandle());
}