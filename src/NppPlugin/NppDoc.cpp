#include "NppDoc.h"

NppDoc::NppDoc(HWND sciHandle) : currentEditView(sciHandle)
{
}

bool NppDoc::isReadOnly()
{
	return ::SendMessage(currentEditView, SCI_GETREADONLY, 0, 0) != 0;
}

Sci_PositionCR NppDoc::getTextLength()
{
	return (Sci_PositionCR) ::SendMessage(currentEditView, SCI_GETLENGTH, 0, 0);
}

QString NppDoc::getWholeText()
{
	auto length = getTextLength();
	char* text = new char[length + sizeof(char)];
	if (text == nullptr)
		return QString();

	text[length] = 0;
	::SendMessage(currentEditView, SCI_GETTEXT, length + sizeof(char), reinterpret_cast<LPARAM>(text));
	QString qtext(text);
	
	if (text)
		delete[] text;

	return qtext;
}