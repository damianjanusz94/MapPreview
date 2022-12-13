#include "GeoLayer.h"
#include "FileHelper.h"
#include "GeoHelper.h"
#include "NppFilesList.h"
#include <gdal/ogrsf_frmts.h>

using namespace Enums;

GeoLayer::GeoLayer(QString file_path, const QString& text) : filePath(file_path)
{
	fileName = FileHelper::getFileName(file_path);
	fileNameWoExt = FileHelper::getFileNameWoExt(file_path);
	isNewFile = FileHelper::isFilePath(file_path);
	pointColor = GeoHelper::getRandomColor();
	lineColor = GeoHelper::getRandomColor();
	polygonColor = GeoHelper::getRandomColor();

	readGeoText(text);
}

void GeoLayer::readGeoText(const QString& geo_text)
{
	try
	{
		GDALDataset* poDS = static_cast<GDALDataset*>(GDALOpenEx(geo_text.toUtf8(), GDAL_OF_VECTOR, nullptr, nullptr, nullptr));
		if (poDS == nullptr)
		{
			return;
		}
		auto poLayer = poDS->GetLayer(0);

		OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();

		poLayer->ResetReading();
		OGRFeature* poFeature;
		while ((poFeature = poLayer->GetNextFeature()) != nullptr)
		{
			for (int iField = 0; iField < poFDefn->GetFieldCount(); iField++)
			{
				OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);

				switch (poFieldDefn->GetType())
				{
				case OFTInteger:
					printf("%d,", poFeature->GetFieldAsInteger(iField));
					break;
				case OFTInteger64:
					printf(CPL_FRMT_GIB ",", poFeature->GetFieldAsInteger64(iField));
					break;
				case OFTReal:
					printf("%.3f,", poFeature->GetFieldAsDouble(iField));
					break;
				case OFTString:
					printf("%s,", poFeature->GetFieldAsString(iField));
					break;
				default:
					printf("%s,", poFeature->GetFieldAsString(iField));
					break;
				}
			}

			OGRGeometry* poGeometry = poFeature->GetGeometryRef();
			if (poGeometry != nullptr)
			{
				if (wkbFlatten(poGeometry->getGeometryType()) == wkbPoint)
				{
					OGRPoint* poPoint = (OGRPoint*)poGeometry;
					poPoint;

				}
			}
			OGRFeature::DestroyFeature(poFeature);
		}

		GDALClose(poDS);
	}
	catch (...)
	{
		
	}
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

