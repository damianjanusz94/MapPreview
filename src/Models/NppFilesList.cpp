#include "NppFilesList.h"
#include "FileHelper.h"

#include <QtCore\QStringList>

NppFilesList::NppFilesList(std::shared_ptr<NppProxy> pNppProxy) : nppProxy(pNppProxy)
{
}

std::vector<NppFile> NppFilesList::readNppFiles()
{
	nppFiles.clear();

	int file_count = nppProxy->getNumberInfo(NPPM_GETNBOPENFILES, PRIMARY_VIEW);
	QStringList file_list = nppProxy->getStringArrayInfo(file_count, NPPM_GETOPENFILENAMESPRIMARY);

	for (const auto& file : file_list)
	{
		NppFile nppFile;
		nppFile.currentPath = file;
		nppFile.fileName = FileHelper::getFileName(file);
		nppFiles.push_back(nppFile);
	}

	return nppFiles;
}
