#ifndef TM_APP_WINDOW_H_
#define TM_APP_WINDOW_H_

#include "ui_MainWindow.h"

#include <TuringMachine.hpp>
#include <QMessageBox>
#include <QTimer>

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

private:
    Ui::MainWindow *ui_;
    QMessageBox *alert_;
    QTimer *timer_, *move_timer_;
    TuringMachine *turing_machine_;
    int middle_cell_;

    void alert(std::string);

    void move();

    void update();
    void updateFiniteTable();
    void updateHeaders();
    void updateStates();
    void updateTape();
};

#endif // TM_APP_WINDOW_H_