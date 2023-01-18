#pragma once

namespace Enums
{
	class GeoExtType
	{
	public:
		enum class ExtType
		{
			unknown,
			GEOJSON,
			GML,
			WKB,
			WKT
		};

	private:
		static inline const std::map<ExtType, QString> fileExtTypeMap
		{
			{ExtType::unknown, "unknown"},
			{ExtType::GEOJSON, "GEOJSON"},
			{ExtType::GML, "GML"},
			{ExtType::WKB, "WKB"},
			{ExtType::WKT, "WKT"}
		};

	public:
		static QString GetGeoExtTypeString(ExtType type)
		{
			auto it = fileExtTypeMap.find(type);
			if (it != fileExtTypeMap.end())
				return it->second;

			return QString("");
		}

		static QString getGeoExtStringOrUnknown(QString extName)
		{
			for (const auto& [key, value] : fileExtTypeMap)
				if (value == extName.toUpper())
					return value;

			return fileExtTypeMap.at(ExtType::unknown);
		}

		static bool isGeoExtType(QString ext)
		{
			for (const auto& [key, value] : fileExtTypeMap)
				if (value == ext.toUpper())
					return true;

			return false;
		}
	};
}
