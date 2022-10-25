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
			emit pointColorChanged(color);
			break;
		case GeoType::LINE:
			lineColor = color;
			emit lineColorChanged(color);
			break;
		case GeoType::POLYGON:
			polygonColor = color;
			emit polygonColorChanged(color);
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

void GeoLayer::setColorButtonConnection(QPushButton* btn_point, QPushButton* btn_line, QPushButton* btn_polygon)
{
	connect(this, &GeoLayer::pointColorChanged, btn_point, [&, btn_point](QColor color) { btn_point->setStyleSheet("background-color : " + color.name()); });
	connect(this, &GeoLayer::lineColorChanged, btn_line, [&, btn_line](QColor color) { btn_line->setStyleSheet("background-color : " + color.name()); });
	connect(this, &GeoLayer::polygonColorChanged, btn_polygon, [&, btn_polygon](QColor color) { btn_polygon->setStyleSheet("background-color : " + color.name()); });
}

