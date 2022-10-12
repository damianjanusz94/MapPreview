#include "NppProxy.h"

#include <QtCore\QList>

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

QStringList NppProxy::getStringArrayInfo(int size, int infoType)
{
	TCHAR** infoValueArray = new TCHAR*[size];
	for (int i = 0; i < size; i++)
	{
		infoValueArray[i] = new TCHAR[MAX_PATH];
	}

	SendMessage(nppData._nppHandle, infoType, (WPARAM)infoValueArray, (LPARAM)size);

	QStringList valueList;
	for (int i = 0; i < size; i++)
	{
		valueList.append(QString::fromWCharArray(infoValueArray[i]));
	}

	for (int i = 0; i < size; i++) 
		delete[] infoValueArray[i];

	delete[] infoValueArray;

	return valueList;
}

int NppProxy::getNumberInfo(int infoType, int subType)
{
	return SendMessage(nppData._nppHandle, infoType, 0, subType);
}

