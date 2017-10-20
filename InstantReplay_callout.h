#pragma once
//#include <QDialog>
#include <QtWidgets/QDialog>
#include <memory>

#include "ui_InstantReplay_callback.h"

class QCloseEvent;

class replayCallout : public QDialog {
	Q_OBJECT

public:
	std::unique_ptr<Ui_replayCallout> ui;
	replayCallout(QWidget *parent);

	void closeEvent(QCloseEvent *event) override;

	public slots:
	void ShowHideDialog();

private:
	//Nothing here
};
