#pragma once

namespace Enums
{
	enum class FileExtType
	{
		unknown,
		GEOJSON,
		WKB,
		WKT
	};

	static const std::map<FileExtType, QString> fileExtTypeMap
	{
		{FileExtType::unknown, "unknown"},
		{FileExtType::GEOJSON, "GEOJSON"},
		{FileExtType::WKB, "WKB"},
		{FileExtType::WKT, "WKT"}
	};

	QString GetFileExtTypeString(FileExtType type)
	{
		auto it = fileExtTypeMap.find(type);
		if (it != fileExtTypeMap.end())
			return it->second;

		return QString("");
	}

	QString GetFileExtTypeString(QString extName)
	{
		for (const auto& [key, value] : fileExtTypeMap)
			if (value == extName.toUpper())
				return value;

		return fileExtTypeMap.at(FileExtType::unknown);
	}
}
