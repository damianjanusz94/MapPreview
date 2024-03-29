#pragma once

#include <QtWidgets\QDialog>
#include <QtWidgets\QPushButton>
#include <QtWidgets\QDialogButtonBox>
#include <QtWidgets\QListWidget>
#include <QtWidgets\QBoxLayout>

#include "../NppPlugin/NppProxy.h"
#include "../Models/NppFilesList.h"


class MpFileAddWindow : public QDialog
{
	Q_OBJECT

	QDialogButtonBox* buttonBox;
	QPushButton* selectAllBtn;
	QPushButton* unselectAllBtn;
	QListWidget* listWidget;
	QVBoxLayout* mainLayout;

	std::shared_ptr<MessageWindow> msgWindow;
	std::shared_ptr<NppFilesList> nppFileList;

	void setupButtons();
	void setupListView();

private slots:
	void selectAllFiles();
	void unselectAllFiles();

public:
	explicit MpFileAddWindow(std::shared_ptr<NppFilesList> pNppFileList, std::shared_ptr<MessageWindow> messageWindow, QWidget* parent = nullptr);
	void fillListView(QStringList currentFiles);
	QStringList getSelectedFiles();
	bool isListEmpty() { return listWidget->count() == 0; }
};

