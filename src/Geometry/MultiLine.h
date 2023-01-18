#pragma once
#include <QtCore\QVector>
#include <QtGui\QPainter>

class MultiLine
{
	QVector<double> vX;
	QVector<double> vY;

public:
	void addPoint(const double& x, const double& y);
	void draw(QPainter& painter) const;
	QPolygonF toQPolygonF() const;
};

