#include "InstantReplay_callout.h"
#include "InstantReplay.h"
#include <obs-frontend-api.h>
#include <obs-module.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QAction>

#include <sstream>

replayCallout *co;

bool get_enabled()
{
	return co->ui->enableCheck->isChecked();
}

int get_wait()
{
	return co->ui->waitSpinBox->value() * 1000;
}

int get_pause()
{
	return co->ui->pauseSpinBox->value();
}

int get_replay()
{
	return co->ui->replaySpinBox->value() * 1000;
}

std::string get_scene()
{
	return co->ui->sceneLineEdit->text().toStdString();
}

bool get_D_mute()
{
	return co->ui->muteDCheck->isChecked();
}

bool get_A_mute()
{
	return co->ui->muteACheck->isChecked();
}

bool get_backup_enabled()
{
	return co->ui->enableBackupCheck->isChecked();
}

std::string get_backup_path()
{
	return co->ui->filePathBackupEdit->text().toStdString();
}

std::string get_replay_source_name()
{
	return co->ui->replaySourceNameEdit->text().toStdString();
}


replayCallout::replayCallout(QWidget *parent)
	: QDialog(parent),
	ui(new Ui_replayCallout)
{
	ui->setupUi(this);

	QObject::connect(ui->closeButton->button(QDialogButtonBox::Close),
		SIGNAL(clicked()), this, SLOT(hide()));
}

void replayCallout::ShowHideDialog()
{
	if(!isVisible())
	{
		setVisible(true);
	}
	else
	{
		setVisible(false);
	}
}

void replayCallout::closeEvent(QCloseEvent* event)
{
	obs_frontend_save();
}

static void save_replay_callout(obs_data_t *save_data, bool saving, void *)
{
	if(saving)
	{
		obs_data_t *obj = obs_data_create();
		QString qstr;
		std::string str;

		obs_data_set_bool(obj, "enable", co->ui->enableCheck->isChecked());
		obs_data_set_int(obj, "wait", co->ui->waitSpinBox->value());
		obs_data_set_int(obj, "pause", co->ui->pauseSpinBox->value());
		obs_data_set_int(obj, "replay", co->ui->replaySpinBox->value());
		qstr = co->ui->sceneLineEdit->text();
		str = qstr.toStdString();
		obs_data_set_string(obj, "scene", str.c_str());
		obs_data_set_bool(obj, "Dmute", co->ui->muteDCheck->isChecked());
		obs_data_set_bool(obj, "Amute", co->ui->muteACheck->isChecked());

	
		// Instant Replay XT extended settings
		obs_data_set_bool(obj, "backup", co->ui->enableBackupCheck->isChecked());
		
		qstr = co->ui->filePathBackupEdit->text();
		str = qstr.toStdString();
		obs_data_set_string(obj, "backupPath", str.c_str());

		qstr = co->ui->replaySourceNameEdit->text();
		str = qstr.toStdString();
		obs_data_set_string(obj, "sourceName", str.c_str());
		//---

		obs_data_set_obj(save_data, "replayCallout_data", obj);

		obs_data_release(obj);
	}
	else
	{
		obs_data_t *obj = obs_data_get_obj(save_data, "replayCallout_data");
		QString qstr;
		if(!obj)
		{
			obj = obs_data_create();
		}
		co->ui->enableCheck->setChecked(obs_data_get_bool(obj, "enable"));
		co->ui->waitSpinBox->setValue(obs_data_get_int(obj, "wait"));
		co->ui->pauseSpinBox->setValue(obs_data_get_int(obj, "pause"));
		co->ui->replaySpinBox->setValue(obs_data_get_int(obj, "replay"));
		qstr = QString::fromLocal8Bit(obs_data_get_string(obj, "scene"));
		co->ui->sceneLineEdit->setText(qstr);
		co->ui->muteDCheck->setChecked(obs_data_get_bool(obj, "Dmute"));
		co->ui->muteACheck->setChecked(obs_data_get_bool(obj, "Amute"));
		
		// Instant Replay XT extended settings
		co->ui->enableBackupCheck->setChecked(obs_data_get_bool(obj, "backup"));
		qstr = QString::fromLocal8Bit(obs_data_get_string(obj, "backupPath"));
		co->ui->filePathBackupEdit->setText(qstr);
		qstr = QString::fromLocal8Bit(obs_data_get_string(obj, "sourceName"));
		co->ui->replaySourceNameEdit->setText(qstr);
		//---

		obs_data_release(obj);
	}
}

static void replay_callout_event(enum obs_frontend_event event, void *)
{
	if(event == OBS_FRONTEND_EVENT_EXIT)
	{
		obs_frontend_save();
	}
}

void replay_callout_init()
{
	QAction *action = (QAction*)obs_frontend_add_tools_menu_qaction(
		obs_module_text("InstantReplaySettings"));
	
	obs_frontend_push_ui_translation(obs_module_get_string);

	QMainWindow *window = (QMainWindow*)obs_frontend_get_main_window();

	co = new replayCallout(window);

	auto cb = []()
	{
		co->ShowHideDialog();
	};

	obs_frontend_pop_ui_translation();

	obs_frontend_add_event_callback(replay_callout_event, nullptr);
	obs_frontend_add_save_callback(save_replay_callout, nullptr);

	action->connect(action, &QAction::triggered, cb);
}
