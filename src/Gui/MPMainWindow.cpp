#include "MpMainWindow.h"

#include <QtCore\QSettings>

MpMainWindow::MpMainWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags)
{
    setObjectName("MainWindow");
    setWindowTitle("MapPreview MainWindow");

    graphicsView = new QGraphicsView(this);
    graphicsView->setMinimumSize(400, 205);
    setCentralWidget(graphicsView);
    graphicsView->setBackgroundBrush(QBrush(QColor(0, 100, 100),Qt::SolidPattern));
    graphicsView->setScene(new QGraphicsScene());

    setupToolbars();
    setupTreeviews();


    readSettings();
}

void MpMainWindow::setupToolbars()
{
    mainToolbar = std::make_unique<MpMainToolbar>(this);
    addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolbar.get());

    infoToolbar = std::make_unique<MpInfoToolbar>(this);
    addToolBar(Qt::ToolBarArea::BottomToolBarArea,infoToolbar.get());
}

void MpMainWindow::setupTreeviews()
{
    Qt::DockWidgetArea area = Qt::RightDockWidgetArea;

    fileTreeview = std::make_unique<MpFileTreeview>(this);

    QDockWidget* dw = new QDockWidget(this);
    const QString name = "Files";
    dw->setObjectName(name);
    dw->setWindowTitle(name);
    dw->setWidget(fileTreeview.get());
    addDockWidget(area, dw);
    dockWidgets.append(dw);

    objectTreeview = std::make_unique<MpObjectTreeview>(this);

    QDockWidget* dwObj = new QDockWidget(this);
    const QString nameObj = "Objects";
    dwObj->setObjectName(nameObj);
    dwObj->setWindowTitle(nameObj);
    dwObj->setWidget(objectTreeview.get());
    addDockWidget(area, dwObj);
    dockWidgets.append(dwObj);
}

void MpMainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings("NotepadPlugin", "MapPreview");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MpMainWindow::readSettings()
{
    QSettings settings("NotepadPlugin", "MapPreview");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}
