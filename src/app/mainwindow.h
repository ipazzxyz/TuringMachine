#pragma once
#include <turingmachine.h>
#include <QMessageBox>
#include <QTimer>
#include "ui_mainwindow.h"
inline QChar normalize(char c)
{
  if (c == '^')
  {
    return QChar(955);
  }
  return c;
}
class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

public slots:
  void on_alphabetSet_clicked();
  void on_stateAdd_clicked();
  void on_stateRemove_clicked();
  void on_stringSet_clicked();
  void on_nextStep_clicked();
  void on_finiteTable_cellChanged(int, int);
  void on_start_clicked();
  void on_stop_clicked();
  void on_pause_clicked();

private:
  TuringMachine *turing_machine_;

  Ui::MainWindow *ui_;

  QMessageBox *alert_;
  QString s_;
  QTimer *timer_;
  QTimer *move_timer_;

  int middle_cell_;

  void setup();
  void setup_timers();

  void update();
  void update_finitetable();
  void update_headers();
  void update_states();
  void update_tape();

  void move();

  void alert(std::string);
};