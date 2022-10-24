#pragma once

#include <QtCore\QString>
#include <QtGui\QColor>

enum class GeoType
{
	POINT,
	LINE,
	POLYGON
};

class GeoLayer
{
	QString fileName;
	QString filePath;
	QString fileNameWoExt;
	QColor pointColor;
	QColor lineColor;
	QColor polygonColor;
	bool isNewFile = false;

public:
	GeoLayer(QString file_path);
	
	QString getFileName() { return fileName; }
	QString getFileNameWoExt() { return fileNameWoExt; }
	QString getFilePath() { return filePath; }
	void setColor(QColor color, GeoType geo_type);
	QColor getColor(GeoType geo_type);
};

