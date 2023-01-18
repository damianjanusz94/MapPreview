#include "GraphicsView.h"
#include <QtGui\QWheelEvent>

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
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    QTransform matrix = transform();
    matrix.translate(targetScenePos.x(), targetScenePos.y())
        .scale(factor, factor)
        .translate(-targetScenePos.x(), -targetScenePos.y());
    setTransform(matrix);

    setTransformationAnchor(oldAnchor);
}
#endif

void GraphicsView::mouseReleaseEvent(QMouseEvent* event)
{
    QGraphicsView::mouseReleaseEvent(event);
    viewport()->setCursor(Qt::CrossCursor);
}
