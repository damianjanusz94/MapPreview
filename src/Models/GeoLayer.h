#pragma once

#include <QtCore\QString>

class GeoLayer
{
	QString fileName;
	QString filePath;
	bool isNewFile = false;

public:
	GeoLayer(QString file_path);
	
	QString getFileName() { return fileName; }
	QString getFilePath() { return filePath; }
};

