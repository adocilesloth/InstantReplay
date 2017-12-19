#pragma once
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_replayCallout
{
public:
	QGridLayout *replayLayout;

	QLabel *enableLabel;
	QCheckBox *enableCheck;

	QLabel *waitLabel;
	QSpinBox *waitSpinBox;
	QLabel *pauseLabel;
	QSpinBox *pauseSpinBox;
	QLabel *replayLabel;
	QSpinBox *replaySpinBox;

	QLabel *sceneLabel;
	QLineEdit *sceneLineEdit;
	QLabel *sourceLabel;
	QLineEdit *sourceLineEdit;

	QLabel *muteDLabel;
	QCheckBox *muteDCheck;
	QLabel *muteALabel;
	QCheckBox *muteACheck;

	QDialogButtonBox *closeButton;

	void setupUi(QDialog *replayCallout)
	{
		if(replayCallout->objectName().isEmpty())
			replayCallout->setObjectName(QStringLiteral("InstantReplay"));
		replayCallout->resize(200, 200);
		replayLayout = new QGridLayout(replayCallout);
		replayLayout->setObjectName(QStringLiteral("replayLayout"));

		enableLabel = new QLabel(replayCallout);
		enableLabel->setObjectName(QStringLiteral("enableLabel"));
		replayLayout->addWidget(enableLabel, 0, 1, 1, 1);

		enableCheck = new QCheckBox(replayCallout);
		enableCheck->setObjectName(QStringLiteral("enableCheck"));
		enableCheck->setChecked(false);
		replayLayout->addWidget(enableCheck, 0, 2, 1, 1);

		waitLabel = new QLabel(replayCallout);
		waitLabel->setObjectName(QStringLiteral("waitLabel"));
		replayLayout->addWidget(waitLabel, 1, 1, 1, 1);

		waitSpinBox = new QSpinBox(replayCallout);
		waitSpinBox->setObjectName(QStringLiteral("waitSpinBox"));
		waitSpinBox->setMinimum(0);
		waitSpinBox->setMaximum(60);
		waitSpinBox->setValue(10);
		replayLayout->addWidget(waitSpinBox, 1, 2, 1, 1);

		pauseLabel = new QLabel(replayCallout);
		pauseLabel->setObjectName(QStringLiteral("pauseLabel"));
		replayLayout->addWidget(pauseLabel, 2, 1, 1, 1);

		pauseSpinBox = new QSpinBox(replayCallout);
		pauseSpinBox->setObjectName(QStringLiteral("pauseSpinBox"));
		pauseSpinBox->setMinimum(0);
		pauseSpinBox->setMaximum(60000);
		pauseSpinBox->setValue(2300);
		replayLayout->addWidget(pauseSpinBox, 2, 2, 1, 1);

		replayLabel = new QLabel(replayCallout);
		replayLabel->setObjectName(QStringLiteral("replayLabel"));
		replayLayout->addWidget(replayLabel, 3, 1, 1, 1);

		replaySpinBox = new QSpinBox(replayCallout);
		replaySpinBox->setObjectName(QStringLiteral("replaySpinBox"));
		replaySpinBox->setMinimum(0);
		replaySpinBox->setMaximum(600);
		replaySpinBox->setValue(19);
		replayLayout->addWidget(replaySpinBox, 3, 2, 1, 1);

		sceneLabel = new QLabel(replayCallout);
		sceneLabel->setObjectName(QStringLiteral("sceneLabel"));
		replayLayout->addWidget(sceneLabel, 4, 1, 1, 1);

		sceneLineEdit = new QLineEdit(replayCallout);
		sceneLineEdit->setObjectName(QStringLiteral("sceneLineEdit"));
		sceneLineEdit->setText("Replay Scene");
		replayLayout->addWidget(sceneLineEdit, 4, 2, 1, 2);

		muteDLabel = new QLabel(replayCallout);
		muteDLabel->setObjectName(QStringLiteral("muteDLabel"));
		replayLayout->addWidget(muteDLabel, 5, 1, 1, 1);

		muteDCheck = new QCheckBox(replayCallout);
		muteDCheck->setObjectName(QStringLiteral("muteDCheck"));
		muteDCheck->setChecked(true);
		replayLayout->addWidget(muteDCheck, 5, 2, 1, 2);

		muteALabel = new QLabel(replayCallout);
		muteALabel->setObjectName(QStringLiteral("muteALabel"));
		replayLayout->addWidget(muteALabel, 6, 1, 1, 1);

		muteACheck = new QCheckBox(replayCallout);
		muteACheck->setObjectName(QStringLiteral("muteACheck"));
		muteACheck->setChecked(true);
		replayLayout->addWidget(muteACheck, 6, 2, 1, 2);

		closeButton = new QDialogButtonBox(replayCallout);
		closeButton->setObjectName(QStringLiteral("buttonBox"));
		closeButton->setStandardButtons(QDialogButtonBox::Close);
		replayLayout->addWidget(closeButton, 7, 3, 1, 1);

		retranslateUi(replayCallout);

		QMetaObject::connectSlotsByName(replayCallout);
	}

	void retranslateUi(QDialog *replayCallout)
	{
		replayCallout->setWindowTitle(QApplication::translate("replayCallout", "InstantReplay", Q_NULLPTR));
		enableLabel->setText(QApplication::translate("replayCallout", "Enable", Q_NULLPTR));
		waitLabel->setText(QApplication::translate("replayCallout", "WritePause", Q_NULLPTR));
		pauseLabel->setText(QApplication::translate("replayCallout", "TransitionPause", Q_NULLPTR));
		replayLabel->setText(QApplication::translate("replayCallout", "ReplayLength", Q_NULLPTR));
		sceneLabel->setText(QApplication::translate("replayCallout", "ReplayScene", Q_NULLPTR));
		muteDLabel->setText(QApplication::translate("replayCallout", "MuteDesktop", Q_NULLPTR));
		muteALabel->setText(QApplication::translate("replayCallout", "MuteAux", Q_NULLPTR));
	}
};

namespace Ui {
	class replayCallout : public Ui_replayCallout {};
} // namespace Ui

QT_END_NAMESPACE
