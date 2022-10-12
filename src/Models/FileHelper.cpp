#include "FileHelper.h"

#include <QtCore\QStringList>

QString FileHelper::getFileName(QString filePath)
{
	QStringList parts = filePath.split("\\");
	return parts.at(parts.size() - 1);
}
