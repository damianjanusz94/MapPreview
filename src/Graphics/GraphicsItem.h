#pragma once
#include <QtGui/QColor>
#include <QtWidgets/QGraphicsItem>
#include "GeometryItem.h"

class GraphicsItem : public QGraphicsItem
{
public:
    GraphicsItem(const QColor& color, int z);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* item, QWidget* widget) override;

private:
    std::shared_ptr<GeometryItem> geomItem;
    QColor color;
    QList<QPointF> stuff;
};
