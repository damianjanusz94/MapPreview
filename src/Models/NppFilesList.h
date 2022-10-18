#pragma once

#include <vector>
#include <QtCore\QString>
#include <QtCore\QMetaType>

#include "../NppPlugin/NppProxy.h"

struct NppFile 
{
	QString fileName;
	QString currentPath;
	QString extension;
};

class NppFilesList
{
	std::vector<NppFile> nppFiles;
	std::shared_ptr<NppProxy> nppProxy;

public:
	NppFilesList(std::shared_ptr<NppProxy> pNppProxy);

	std::vector<NppFile> readNppFiles();
};

