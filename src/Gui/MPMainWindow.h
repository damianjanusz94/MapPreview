#pragma once

#include <QtWidgets\QMainWindow>

class ToolBar;
QT_FORWARD_DECLARE_CLASS(QMenu)

class MPMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef QMap<QString, QSize> CustomSizeHintMap;

    explicit MPMainWindow(const CustomSizeHintMap& customSizeHints,
        QWidget* parent = nullptr,
        Qt::WindowFlags flags = { });

public slots:
    void actionTriggered(QAction* action);
    void saveLayout();
    void loadLayout();
    void switchLayoutDirection();
    void setDockOptions();

    void createDockWidget();
    void destroyDockWidget(QAction* action);

    void about();

private:
    void setupToolBar();
    void setupMenuBar();
    void setupDockWidgets(const CustomSizeHintMap& customSizeHints);

    QList<ToolBar*> toolBars;
    QMenu* dockWidgetMenu;
    QMenu* mainWindowMenu;
    QList<QDockWidget*> extraDockWidgets;
    QMenu* destroyDockWidgetMenu;
};




