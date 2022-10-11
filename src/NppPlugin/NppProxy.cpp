#include "NppProxy.h"

NppProxy::NppProxy(NppData pNppData) : nppData(pNppData)
{
}

QString NppProxy::getCurrentDocPathInfo(int infoType)
{
	TCHAR infoValue[MAX_PATH];
	ZeroMemory(infoValue, MAX_PATH);

	SendMessage(nppData._nppHandle, infoType, 0, (LPARAM)infoValue);

	return QString::fromWCharArray(infoValue);
}
