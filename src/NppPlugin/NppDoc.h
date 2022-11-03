#pragma once

#include <QtCore\QString>

#include "NppProxy.h"

class NppDoc
{
	std::shared_ptr<NppProxy> nppProxy;
	HWND currentEditView;

public:
	NppDoc(HWND sciHandle);

	bool isReadOnly();
	Sci_PositionCR getTextLength();
	QString getWholeText();

};