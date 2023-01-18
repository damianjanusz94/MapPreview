#include "MultiLine.h"

void MultiLine::addPoint(const double& x, const double& y)
{
	vX.push_back(x);
	vY.push_back(y);
}

void MultiLine::draw(QPainter& painter) const
{
	painter.drawPolyline(toQPolygonF());
}

QPolygonF MultiLine::toQPolygonF() const
{
	QPolygonF points(vX.size());

	for (unsigned int i = 0; i < vX.size(); i++)
	{
		points.push_back(QPointF(vX[i], vY[i]));
	}

	return points;
}
