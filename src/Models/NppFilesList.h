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
	QString text;
};

class NppFilesList
{
	std::shared_ptr<NppProxy> nppProxy;

public:
	NppFilesList(std::shared_ptr<NppProxy> pNppProxy);

	std::vector<NppFile> readNppFilesInfo();

	void countAllFiles(int& main_count, int& second_count);
	bool isNextDoc(int* iter, int main_count, int second_count);

	QString readDocText(const QString& file_path);

};

