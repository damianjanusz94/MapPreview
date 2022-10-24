#include "GeoHelper.h"

#include <QtCore\QRandomGenerator>

QColor GeoHelper::getRandomColor()
{
	return QColor(QRandomGenerator::global()->bounded(0, 255),
				  QRandomGenerator::global()->bounded(0, 255),
				  QRandomGenerator::global()->bounded(0, 255));
}
