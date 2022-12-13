#include "NppFilesList.h"

#include <QtCore\QStringList>

#include "FileHelper.h"
#include "../NppPlugin/NppDoc.h"

NppFilesList::NppFilesList(std::shared_ptr<NppProxy> pNppProxy, std::shared_ptr<MessageWindow> messageWindow) : nppProxy(pNppProxy), msgWindow(messageWindow)
{
}

std::vector<NppFile> NppFilesList::readNppFilesInfo()
{
	std::vector<NppFile> nppFiles;

	int file_count_main, file_count_second = 0;

	countAllFiles(file_count_main, file_count_second);

	QStringList file_list = nppProxy->getStringArrayInfo(file_count_main, NPPM_GETOPENFILENAMESPRIMARY) 
						  + nppProxy->getStringArrayInfo(file_count_second, NPPM_GETOPENFILENAMESSECOND);

	for (const auto& file : file_list)
	{
		NppFile nppFile;
		nppFile.currentPath = FileHelper::getFilePath(file);
		nppFile.fileName = FileHelper::getFileName(file);
		nppFile.extension = FileHelper::getFileExtension(file);
		nppFiles.push_back(nppFile);
	}

	return nppFiles;
}

void NppFilesList::countAllFiles(int& main_count, int& second_count)
{
	main_count = nppProxy->getNumberInfo(NPPM_GETNBOPENFILES, PRIMARY_VIEW);
	second_count = nppProxy->getNumberInfo(NPPM_GETNBOPENFILES, SECOND_VIEW);

	if (nppProxy->getNumberInfo(NPPM_GETCURRENTDOCINDEX, MAIN_VIEW) < 0)
		main_count = 0;

	if (nppProxy->getNumberInfo(NPPM_GETCURRENTDOCINDEX, SUB_VIEW) < 0)
		second_count = 0;
}

bool NppFilesList::isNextDoc(int* iter, int main_count, int second_count) 
{
	if (*iter < 0 || *iter >= (main_count + second_count))
		return false;
	
	if (*iter < main_count) 
	{
		nppProxy->sendMessage(NPPM_ACTIVATEDOC, MAIN_VIEW, (*iter));
	}
	else if (*iter >= main_count && *iter < main_count + second_count) 
	{
	    auto idx = (*iter) - main_count;
		nppProxy->sendMessage(NPPM_ACTIVATEDOC, SUB_VIEW, idx);
	}
	else 
	{
	    return false;
	}
	
	++(*iter);
	return true;
}

QString NppFilesList::readDocText(const QString& file_path)
{
	int file_count_main, file_count_second, iterator = 0;
	countAllFiles(file_count_main, file_count_second);

	while (isNextDoc(&iterator, file_count_main, file_count_second))
	{
		if (nppProxy->getCurrentFilePath() == file_path)
		{
			NppDoc doc{ nppProxy->getCurrentSciHandle() };
			return doc.getWholeText();
		}
	}

	return QString("");
}