#pragma once

#include <QtWidgets\QMainWindow>
#include <QtWidgets\QDockWidget>
#include <QtWidgets\QGraphicsView>
#include <QtWidgets\QDockWidget>

#include "MpFileTreeview.h"
#include "MpObjectTreeview.h"
#include "MpMainToolbar.h"
#include "MpInfoToolbar.h"

class MpMainWindow : public QMainWindow
{
	Q_OBJECT;

	QList<QDockWidget*> dockWidgets;
	QGraphicsView* graphicsView;
	std::unique_ptr<MpFileTreeview> fileTreeview;
	std::unique_ptr<MpObjectTreeview> objectTreeview;
	std::unique_ptr<MpMainToolbar> mainToolbar;
	std::unique_ptr<MpInfoToolbar> infoToolbar;
	
public:
	explicit MpMainWindow(QWidget* parent = nullptr, Qt::WindowFlags flags = { });

private:
	void setupToolbars();
	void setupTreeviews();
	void readSettings();

protected:
	void closeEvent(QCloseEvent* event) override;

};

