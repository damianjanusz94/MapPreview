#include "NppFilesList.h"

NppFilesList::NppFilesList(std::shared_ptr<NppProxy> pNppProxy) : nppProxy(pNppProxy)
{
}

std::vector<NppFile> NppFilesList::readNppFiles()
{
	nppFiles.clear();

	NppFile nppFile;
	nppFile.currentPath = nppProxy->getCurrentDocPathInfo(NPPM_GETFULLCURRENTPATH);
	nppFile.fileName = nppProxy->getCurrentDocPathInfo(NPPM_GETFILENAME);

	nppFiles.push_back(nppFile);

	return nppFiles;
}
