#pragma once

#include <QtCore\QString>

class FileHelper
{
public:
	static QString getFilePath(QString filePath);
	static QString getFileName(QString filePath);
	static QString getFileNameWoExt(QString filePath);
	static QString getFileExtension(QString filePath);
	static bool isFilePath(QString filePath);
};

