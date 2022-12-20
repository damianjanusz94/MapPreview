#pragma once
#include <QtWidgets\QGraphicsView>

class MainWindow;

class GraphicsView : public QGraphicsView
{
	Q_OBJECT
public:
	GraphicsView(MainWindow* v) : QGraphicsView(), view_(v)
	{

	}

protected:
#if QT_CONFIG(wheelevent)
	void wheelEvent(QWheelEvent*) override;
	void zoomAt(QPointF centerPos, double factor);
#endif

	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	MainWindow* view_;
};
