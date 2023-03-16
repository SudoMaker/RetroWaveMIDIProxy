/*
    This file is part of RetroWaveMIDIProxyGUI
    Copyright (C) 2023 Reimu NotMoe <reimu@sudomaker.com>
    Copyright (C) 2023 Yukino Song <yukino@sudomaker.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as
    published by the Free Software Foundation, either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <mutex>

#include <QMainWindow>

#include <QFile>
#include <QFileDialog>
#include <QTimer>
#include <QMessageBox>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <RtMidi.h>

#include <adlmidi.h>
#include <adlmidi_midiplay.hpp>
#include <adlmidi_opl3.hpp>
#include <chips/opl_chip_base.h>
#include <midi_sequencer.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

	void spp_refresh_available();
	void bank_refresh_available();
	void midi_refresh_available();

	bool start();
	void stop();
	void midi_init();

	void rw_buf_reset();
	void rw_buf_queue(uint16_t addr, uint8_t data);
	void rw_buf_flush();

	static void midi_on_receive(double timeStamp, std::vector<unsigned char> *message, void *userData);
	static void midi_on_error(RtMidiError::Type type, const std::string &errorText, void *userData);
private slots:
	void on_btn_spp_refresh_clicked();

	void on_cb_bank_list_activated(int index);

	void on_cb_volmodel_list_activated(int index);

	void on_btn_midi_refresh_clicked();

	void on_cb_midiport_list_activated(int index);

	void on_btn_start_stop_clicked();

public slots:
	void a_adl_timer_timeout();


private:
	Ui::MainWindow *ui;

	QSerialPort *spp = nullptr;
	QVector<uint8_t> rw_buf;

	int bank_id = 58;
	QString bank_path, bank_last_dir;
	int volmodel_id = 0;

	RtMidiIn *midiin = nullptr;
	int midi_port = -1;

	ADL_MIDIPlayer *adl_midi_player = nullptr;
	MidiSequencer *adl_midi_sequencer = nullptr;
	QTimer *tmr_adl = nullptr;
	bool started = false;

	std::mutex rw_buf_lock;
};
