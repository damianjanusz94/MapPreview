#pragma once

#include <QtCore\QString>
#include "PluginInterface.h"

class NppProxy
{
	NppData nppData;

public:
	NppProxy(NppData pNppData);
	QString getCurrentDocPathInfo(int infoType);
	QStringList getStringArrayInfo(int size, int infoType);
	int getNumberInfo(int infoType, int subType);

};

