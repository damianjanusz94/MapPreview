#pragma once

#include <QtCore\QObject>
#include <QtCore\QString>
#include <QtGui\QColor>
#include <QtWidgets\QPushButton>

#include "../Enums/GeoType.h"

class GeoLayer : public QObject
{
	Q_OBJECT

	QString fileName;
	QString filePath;
	QString fileNameWoExt;
	QColor pointColor;
	QColor lineColor;
	QColor polygonColor;
	bool isNewFile = false;

	void readGeoText(const QString& geo_text);

signals:
	void pointColorChanged(QColor color);
	void lineColorChanged(QColor color);
	void polygonColorChanged(QColor color);
	

public:
	GeoLayer(QString file_path, const QString& text);
	
	QString getFileName() { return fileName; }
	QString getFileNameWoExt() { return fileNameWoExt; }
	QString getFilePath() { return filePath; }
	void setColor(QColor color, Enums::GeoType geo_type);
	QColor getColor(Enums::GeoType geo_type);
	void setColorButtonConnection(QPushButton* btn_point, QPushButton* btn_line, QPushButton* btn_polygon);
};

