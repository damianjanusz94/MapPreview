#pragma once

#include <QtWidgets\QMainWindow>
#include <QtWidgets\QDockWidget>

#include "MpFileTreeview.h"
#include "MpObjectTreeview.h"
#include "MpMainToolbar.h"
#include "MpInfoToolbar.h"
#include "MpFileTvToolbar.h"
#include "ObjectTvToolbar.h"
#include "../NppPlugin/NppProxy.h"
#include "../Models/ObjectTreeModel.h"
#include "MessageWindow.h"
#include "../Graphics/GraphicsScene.h"
#include "../Graphics/GraphicsView.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT;

	QList<QDockWidget*> dockWidgets;
	std::shared_ptr<GraphicsView> graphicsView;
	std::shared_ptr<GraphicsScene> scene;
	std::shared_ptr<MpFileTreeview> fileTreeview;
	std::unique_ptr<MpFileTvToolbar> fileTvToolbar;
	std::unique_ptr<ObjectTvToolbar> objectTvToolbar;
	std::shared_ptr<MpObjectTreeview> objectTreeview;
	std::unique_ptr<MpMainToolbar> mainToolbar;
	std::shared_ptr<MpInfoToolbar> infoToolbar;

	std::shared_ptr<NppProxy> nppProxy;
	std::shared_ptr<FileTreeModel> fileTreeModel;
	std::shared_ptr<ObjectTreeModel> objectTreemodel;
	std::shared_ptr<MessageWindow> messageWindow;

	int currentZoom = 250;
	
public:
	explicit MainWindow(std::shared_ptr<NppProxy> pNppProxy, QWidget* parent = nullptr, Qt::WindowFlags flags = { });

private:
	void setupToolbars();
	void setupTreeDockWidgets();
	void setupFileDockWidget(Qt::DockWidgetArea area);
	void setupObjectDockWidget(Qt::DockWidgetArea area);
	void setupMessageDockWidget(Qt::DockWidgetArea area);
	void readSettings();
	void populateScene();

protected:
	void closeEvent(QCloseEvent* event) override;

public slots:
	void zoomInBy(int level);
	void zoomOutBy(int level);

private slots:
	void setupMatrix();

};

