#include "MainWindow.h"

#include <QtCore\QSettings>
#include <QtWidgets\QBoxLayout>
#include "../Graphics/GraphicsItem.h"

MainWindow::MainWindow(std::shared_ptr<NppProxy> pNppProxy, QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), nppProxy(pNppProxy)
{
    setObjectName("MainWindow");
    setWindowTitle("MapPreview MainWindow");

    scene = std::make_shared<QGraphicsScene>();
    graphicsView = std::make_shared<GraphicsView>(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, false);
    graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    graphicsView->setScene(scene.get());
    graphicsView->viewport()->setCursor(Qt::CrossCursor);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setupMatrix();
    setCentralWidget(graphicsView.get());

    //graphicsView->setBackgroundBrush(QBrush(QColor(0, 100, 100),Qt::SolidPattern));

    setupMessageDockWidget(Qt::BottomDockWidgetArea);
    setupToolbars();
    setupTreeDockWidgets();

    readSettings();
    populateScene();
}

void MainWindow::setupToolbars()
{
    mainToolbar = std::make_unique<MpMainToolbar>(this, messageWindow);
    addToolBar(Qt::ToolBarArea::TopToolBarArea, mainToolbar.get());

    infoToolbar = std::make_unique<MpInfoToolbar>(this, messageWindow);
    addToolBar(Qt::ToolBarArea::BottomToolBarArea,infoToolbar.get());
}

void MainWindow::setupTreeDockWidgets()
{
    Qt::DockWidgetArea area = Qt::RightDockWidgetArea;
    
    setupFileDockWidget(area);
    setupObjectDockWidget(area);
}

void MainWindow::setupFileDockWidget(Qt::DockWidgetArea area)
{
    objectTreemodel = std::make_shared<ObjectTreeModel>(messageWindow);
    objectTreeview = std::make_shared<MpObjectTreeview>(objectTreemodel, messageWindow);
    fileTreeModel = std::make_shared<FileTreeModel>(objectTreemodel, messageWindow);
    fileTreeview = std::make_shared<MpFileTreeview>(fileTreeModel, messageWindow);
    fileTvToolbar = std::make_unique<MpFileTvToolbar>(nppProxy, fileTreeview, fileTreeModel, objectTreeview, messageWindow);
    objectTvToolbar = std::make_unique<ObjectTvToolbar>(objectTreeview, messageWindow);

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

void MainWindow::setupObjectDockWidget(Qt::DockWidgetArea area)
{
    QWidget* widget = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout(widget);
    vLayout->addWidget(objectTvToolbar.get());
    vLayout->addWidget(objectTreeview.get());
    vLayout->setContentsMargins(0, 0, 0, 0);

    QDockWidget* dwObj = new QDockWidget(this);
    const QString nameObj = "Objects";
    dwObj->setObjectName(nameObj);
    dwObj->setWindowTitle(nameObj);
    dwObj->setWidget(widget);
    dwObj->setMaximumHeight(400);
    addDockWidget(area, dwObj);
    dockWidgets.append(dwObj);
}

void MainWindow::setupMessageDockWidget(Qt::DockWidgetArea area)
{
    messageWindow = std::make_shared<MessageWindow>();
    QWidget* widget = new QWidget(this);
    QVBoxLayout* vLayout = new QVBoxLayout(widget);
    vLayout->addWidget(messageWindow.get());
    vLayout->setContentsMargins(0, 0, 0, 0);

    QDockWidget* dwObj = new QDockWidget(this);
    const QString nameObj = "Messages";
    dwObj->setObjectName(nameObj);
    dwObj->setWindowTitle(nameObj);
    dwObj->setWidget(widget);
    dwObj->setMaximumHeight(150);
    addDockWidget(area, dwObj);
    dockWidgets.append(dwObj);
}


void MainWindow::closeEvent(QCloseEvent* event)
{
    QSettings settings("NotepadPlugin", "MapPreview");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    QMainWindow::closeEvent(event);
}

void MainWindow::readSettings()
{
    QSettings settings("NotepadPlugin", "MapPreview");
    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());
}

void MainWindow::setupMatrix()
{
    qreal scale = qPow(qreal(2), (currentZoom - 250) / qreal(50));

    QTransform matrix;
    matrix.scale(scale, scale);
    graphicsView.get()->setTransform(matrix);
}

void MainWindow::zoomInBy(int level)
{
    currentZoom += level;
    setupMatrix();
}

void MainWindow::zoomOutBy(int level)
{
    currentZoom -= level;
    setupMatrix();
}

void MainWindow::populateScene()
{
    int xx = 0;
    int nitems = 0;
    for (int i = -11000; i < 11000; i += 110) {
        ++xx;
        int yy = 0;
        for (int j = -7000; j < 7000; j += 70) {
            ++yy;

            QColor color(200,100,100);
            QGraphicsItem* item = new GraphicsItem(color, 1);
            item->setPos(QPointF(i, j));
            scene->addItem(item);

            ++nitems;
        }
    }
}

#if QT_CONFIG(wheelevent)
void GraphicsView::wheelEvent(QWheelEvent* e)
{
    double angle = e->angleDelta().y();

    double factor = qPow(1.0015, angle);
    zoomAt(e->position(), factor);

}

void GraphicsView::zoomAt(QPointF centerPos, double factor)
{
    QPointF targetScenePos = mapToScene(centerPos.toPoint());
    ViewportAnchor oldAnchor = this->transformationAnchor();
    setTransformationAnchor(QGraphicsView::NoAnchor);

    QTransform matrix = transform();
    matrix.translate(targetScenePos.x(), targetScenePos.y())
        .scale(factor, factor)
        .translate(-targetScenePos.x(), -targetScenePos.y());
    setTransform(matrix);

    setTransformationAnchor(oldAnchor);
}

#endif