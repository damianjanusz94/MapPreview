#pragma once

#include <memory>

#include "NppPlugin/NppPlugin.h"
#include "NppPlugin/DockingFeature/DockingDlgInterface.h"
#include "QtMfc/qwinwidget.h"
#include "Gui/MpMainWindow.h"

class MapPreviewWindow : public DockingDlgInterface
{
private:
	HANDLE hModule;
	HWND winId = 0;
	bool ready = false;
	bool ownApplication = false;

	std::shared_ptr<QWinWidget> qtMainWidget;
	std::shared_ptr<MpMainWindow> mpMainWindow;

	void setParent(HWND parent) { _hParent = parent; }

	void InitializeDialog(NppData nppData);
	void InitializeResources(NppData nppData);
	void InitializeDependencies();

	INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
	void OnSize(HWND hDlg);
	void OnDestroy();

public:
	MapPreviewWindow(HANDLE hModule);
	~MapPreviewWindow();

	void Display(bool toShow = true) const;
	void Initialize(NppData nppData);

};

