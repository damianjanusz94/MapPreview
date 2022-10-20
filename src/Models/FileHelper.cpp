#include "FileHelper.h"

#include <QtCore\QStringList>

QString FileHelper::getFilePath(QString filePath)
{
	if (!filePath.contains("\\"))
		return QString("");

	return filePath;
}

QString FileHelper::getFileName(QString filePath)
{
	if (!filePath.contains("\\"))
		return filePath;

	QStringList parts = filePath.split("\\");
	return parts.at(parts.size() - 1);
}

QString FileHelper::getFileExtension(QString filePath)
{
	if (!filePath.contains("."))
		return QString("");

	QStringList parts = filePath.split(".");
	return parts.at(parts.size() - 1);
}

bool FileHelper::isFilePath(QString filePath)
{
	return filePath.contains("\\");
}
