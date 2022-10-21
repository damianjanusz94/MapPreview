#pragma once

#include <QtCore\QString>

class GeoLayer
{
	QString fileName;
	QString filePath;
	QString fileNameWoExt;
	bool isNewFile = false;

public:
	GeoLayer(QString file_path);
	
	QString getFileName() { return fileName; }
	QString getFileNameWoExt() { return fileNameWoExt; }
	QString getFilePath() { return filePath; }
};

