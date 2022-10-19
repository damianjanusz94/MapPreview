#include "MpMainWindow.h"

#include <QtCore\QSettings>
#include <QtWidgets\QBoxLayout>

MpMainWindow::MpMainWindow(std::shared_ptr<NppProxy> pNppProxy, QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), nppProxy(pNppProxy)
{
    setObjectName("MainWindow");
    setWindowTitle("MapPreview MainWindow");

    graphicsView = new QGraphicsView(this);
    setCentralWidget(graphicsView);
    //graphicsView->setBackgroundBrush(QBrush(QColor(0, 100, 100),Qt::SolidPattern));
    graphicsView->setScene(new QGraphicsScene());

    setupToolbars();
    setupTreeDockWidgets();

    readSettings();
}

void MpMainWindow::setupToolbars()
{
    mainToolbar = std::make_unique<MpMainToolbar>(this);
    addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolbar.get());

    infoToolbar = std::make_unique<MpInfoToolbar>(this);
    addToolBar(Qt::ToolBarArea::BottomToolBarArea,infoToolbar.get());
}

void MpMainWindow::setupTreeDockWidgets()
{
    Qt::DockWidgetArea area = Qt::RightDockWidgetArea;

    setupFileDockWidget(area);

    objectTreeview = std::make_unique<MpObjectTreeview>(this);

    QDockWidget* dwObj = new QDockWidget(this);
    const QString nameObj = "Objects";
    dwObj->setObjectName(nameObj);
    dwObj->setWindowTitle(nameObj);
    dwObj->setWidget(objectTreeview.get());
    dwObj->setMaximumHeight(200);
    addDockWidget(area, dwObj);
    dockWidgets.append(dwObj);
}

void MpMainWindow::setupFileDockWidget(Qt::DockWidgetArea area)
{
    fileTreeModel = std::make_unique<FileTreeModel>(this);
    fileTreeview = std::make_shared<MpFileTreeview>(fileTreeModel);
    fileTvToolbar = std::make_unique<MpFileTvToolbar>(nppProxy, fileTreeview, fileTreeModel);

    QWidget* widget = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout(widget);
    vLayout->addWidget(fileTvToolbar.get());
    vLayout->addWidget(fileTreeview.get());
    vLayout->setContentsMargins(0, 0, 0, 0);

    QDockWidget* dw = new QDockWidget(this);
    const QString name = "Files";
    dw->setObjectName(name);
    dw->setWindowTitle(name);
    dw->setWidget(widget);
    dw->setMinimumWidth(400);
    addDockWidget(area, dw);
    dockWidgets.append(dw);
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
