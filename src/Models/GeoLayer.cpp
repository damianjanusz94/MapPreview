#include "GeoLayer.h"
#include "FileHelper.h"
#include "GeoHelper.h"


GeoLayer::GeoLayer(QString file_path) : filePath(file_path)
{
	fileName = FileHelper::getFileName(file_path);
	fileNameWoExt = FileHelper::getFileNameWoExt(file_path);
	isNewFile = FileHelper::isFilePath(file_path);
	pointColor = GeoHelper::getRandomColor();
	lineColor = GeoHelper::getRandomColor();
	polygonColor = GeoHelper::getRandomColor();
}

void GeoLayer::setColor(QColor color, GeoType geo_type)
{
	switch (geo_type)
	{
		case GeoType::POINT:
			pointColor = color;
			break;
		case GeoType::LINE:
			lineColor = color;
			break;
		case GeoType::POLYGON:
			polygonColor = color;
			break;
		default:
			break;
	}
}

QColor GeoLayer::getColor(GeoType geo_type)
{
	switch (geo_type)
	{
		case GeoType::POINT:
			return pointColor;
		case GeoType::LINE:
			return lineColor;
		case GeoType::POLYGON:
			return polygonColor;
		default:
			return QColor();
	}
}

