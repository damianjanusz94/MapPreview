#include "GraphicsItem.h"
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QStyleOptionGraphicsItem>

GraphicsItem::GraphicsItem(const QColor& color, int z)
{
    this->color = color;
    setZValue(z);

    setAcceptHoverEvents(true);
}

QRectF GraphicsItem::boundingRect() const
{
    return geomItem->boundingRect();
}

QPainterPath GraphicsItem::shape() const
{
    QPainterPath path;
    path.addRect(geomItem->boundingRect());
    return path;
}

void GraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
    Q_UNUSED(widget);

    QColor fillColor = color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.lighter(125);

    QPen oldPen = painter->pen();
    QPen pen = oldPen;

    pen.setWidth(0);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.darker(option->state & QStyle::State_Sunken ? 120 : 100)));

    static const QPointF points[4] = 
    {
        QPointF(10.0, 80.0),
        QPointF(20.0, 10.0),
        QPointF(80.0, 30.0),
        QPointF(90.0, 70.0)
    };

    painter->drawPolygon(points, 4);
    painter->setBrush(b);
}

