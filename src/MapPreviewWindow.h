#pragma once

#include <memory>

#include "NppPlugin/NppPlugin.h"
#include "NppPlugin/DockingFeature/DockingDlgInterface.h"

class MapPreviewWindow : public DockingDlgInterface
{
private:
	HANDLE hModule;
	bool ready = false;
	bool ownApplication = false;

	HWND winId = 0;
	//std::unique_ptr<QWinWidget> qtWindow;
	//std::unique_ptr<MainWindow> mainWin;

	void setParent(HWND parent) { _hParent = parent; }

	void InitializeDialog(NppData nppData);
	void InitializeResources(NppData nppData);
	void InitializeDependencies();

	INT_PTR CALLBACK run_dlgProc(UINT message, WPARAM wParam, LPARAM lParam);
	void OnSize(HWND hDlg);

public:
	MapPreviewWindow(HANDLE hModule);
	~MapPreviewWindow();

	void Display(bool toShow = true) const;
	void Initialize(NppData nppData);

};

