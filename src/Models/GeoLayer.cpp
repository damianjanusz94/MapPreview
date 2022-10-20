#include "GeoLayer.h"
#include "FileHelper.h"

GeoLayer::GeoLayer(QString file_path) : filePath(file_path)
{
	fileName = FileHelper::getFileName(file_path);
	isNewFile = FileHelper::isFilePath(file_path);
}
