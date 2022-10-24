#pragma once

#include <QtWidgets\QMainWindow>
#include <QtWidgets\QDockWidget>
#include <QtWidgets\QGraphicsView>
#include <QtWidgets\QDockWidget>

#include "MpFileTreeview.h"
#include "MpObjectTreeview.h"
#include "MpMainToolbar.h"
#include "MpInfoToolbar.h"
#include "MpFileTvToolbar.h"
#include "ObjectTvToolbar.h"
#include "../NppPlugin/NppProxy.h"
#include "../Models/ObjectTreeModel.h"


class MpMainWindow : public QMainWindow
{
	Q_OBJECT;

	QList<QDockWidget*> dockWidgets;
	QGraphicsView* graphicsView;
	std::shared_ptr<MpFileTreeview> fileTreeview;
	std::unique_ptr<MpFileTvToolbar> fileTvToolbar;
	std::unique_ptr<ObjectTvToolbar> objectTvToolbar;
	std::shared_ptr<MpObjectTreeview> objectTreeview;
	std::unique_ptr<MpMainToolbar> mainToolbar;
	std::unique_ptr<MpInfoToolbar> infoToolbar;

	std::shared_ptr<NppProxy> nppProxy;
	std::shared_ptr<FileTreeModel> fileTreeModel;
	std::shared_ptr<ObjectTreeModel> objectTreemodel;
	
public:
	explicit MpMainWindow(std::shared_ptr<NppProxy> pNppProxy, QWidget* parent = nullptr, Qt::WindowFlags flags = { });

private:
	void setupToolbars();
	void setupTreeDockWidgets();
	void setupFileDockWidget(Qt::DockWidgetArea area);
	void setupObjectDockWidget(Qt::DockWidgetArea area);
	void readSettings();

protected:
	void closeEvent(QCloseEvent* event) override;

};

