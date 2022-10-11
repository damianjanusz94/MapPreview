#pragma once

#include <QtCore\QString>
#include "PluginInterface.h"

class NppProxy
{
	NppData nppData;

public:
	NppProxy(NppData pNppData);
	QString getCurrentDocPathInfo(int infoType);
};

