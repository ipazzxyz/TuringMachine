#include "mainwindow.h"

#include <iostream>

MainWindow::MainWindow() : ui_(new Ui::MainWindow), alert_(new QMessageBox), timer_(new QTimer), move_timer_(new QTimer), turing_machine_(new TuringMachine(1e6))
{
    setup();
    update();
}
MainWindow::~MainWindow()
{
    delete ui_, alert_, timer_, move_timer_, turing_machine_;
}

void MainWindow::on_alphabetSet_clicked()
{
    try
    {
        turing_machine_->setAlphabet(ui_->alphabetParameter->text().toStdString(), ui_->alphabetAdditionalParameter->text().toStdString());
    }
    catch (exception::AlphabetIntersection exception)
    {
        alert(exception.what());
    }
    catch (exception::UnallowedSymbol exception)
    {
        alert(exception.what());
    }
    update();
    return;
}
void MainWindow::on_stateAdd_clicked()
{
    turing_machine_->stateAdd();
    update();
    return;
}
void MainWindow::on_stateRemove_clicked()
{
    try
    {
        turing_machine_->stateRemove();
    }
    catch (exception::DeleteNothing exception)
    {
        alert(exception.what());
    }
    update();
    return;
}
void MainWindow::on_pause_clicked()
{
    timer_->stop();
}
void MainWindow::on_stringSet_clicked()
{
    try
    {
        turing_machine_->setString(ui_->stringParameter->text().toStdString());
    }
    catch (exception::UnknownSymbol exception)
    {
        alert(exception.what());
    }
    update();
    return;
}
void MainWindow::on_nextStep_clicked()
{
    try
    {
        turing_machine_->makeStep();
    }
    catch (exception::InactiveMachine exception)
    {
        alert(exception.what());
    }
    catch (exception::SymbolNotFromAlphabetOnTape exception)
    {
        alert(exception.what());
    }
    catch (exception::NoExitFunction exception)
    {
        alert(exception.what());
    }
    update();
    return;
}
void MainWindow::on_finiteTable_cellChanged(int row, int column)
{
    try
    {
        turing_machine_->setFunction(row, ui_->finiteTable->takeHorizontalHeaderItem(column)->text().toStdString()[0], ui_->finiteTable->item(row, column)->text().toStdString());
    }
    catch (exception::BadFunction exception)
    {
        alert(exception.what());
    }
    catch (exception::UnknownSymbol exception)
    {
        alert(exception.what());
    }
    update();
    return;
}
void MainWindow::on_start_clicked()
{
    timer_->start();
}
void MainWindow::on_stop_clicked()
{
    turing_machine_->reset();
    update();
}

void MainWindow::setup()
{
    setFixedSize(960, 512);
    ui_->setupUi(this);
    middle_cell_ = turing_machine_->currentIndex();
    setup_timers();
    return;
}
void MainWindow::setup_timers()
{
    connect(timer_, &QTimer::timeout, this, &MainWindow::on_nextStep_clicked);
    connect(move_timer_, &QTimer::timeout, this, &MainWindow::move);
    move_timer_->start();
    move_timer_->setInterval(10);
    return;
}

void MainWindow::update()
{
    timer_->setInterval(1000. / (ui_->speedParameter->value() + 1));
    update_finitetable();
    update_tape();
    return;
}
void MainWindow::update_finitetable()
{
    update_headers();
    update_states();
    return;
}
void MainWindow::update_headers()
{
    std::set<char> &main_alphabet(turing_machine_->mainAlphabet());
    std::set<char> &additional_alphabet(turing_machine_->additionalAlphabet());
    ui_->finiteTable->setColumnCount(main_alphabet.size() + additional_alphabet.size());
    std::set<char>::iterator it = main_alphabet.begin();
    for (int i = 0; i < turing_machine_->mainAlphabet().size(); ++i)
    {
        if (*it == '^')
        {
            ++it;
            --i;
        }
        else
        {
            ui_->finiteTable->setHorizontalHeaderItem(i, new QTableWidgetItem(normalize(*(it++))));
        }
    }
    ui_->finiteTable->setHorizontalHeaderItem(turing_machine_->mainAlphabet().size() - 1, new QTableWidgetItem(QChar('^')));
    it = additional_alphabet.begin();
    for (int i = 0; i < additional_alphabet.size(); ++i)
    {
        ui_->finiteTable->setHorizontalHeaderItem(main_alphabet.size() + i, new QTableWidgetItem(normalize(*(it++))));
    }
    ui_->finiteTable->setRowCount(turing_machine_->finiteTableSize());
    for (int row = 0; row < ui_->finiteTable->rowCount(); ++row)
    {
        ui_->finiteTable->setVerticalHeaderItem(row, new QTableWidgetItem(QString::fromStdString(std::to_string(row))));
    }
    return;
}
void MainWindow::update_states()
{
    for (int column = 0; column < ui_->finiteTable->columnCount(); ++column)
    {
        for (int row = 0; row < ui_->finiteTable->rowCount(); ++row)
        {
            QTableWidgetItem *cell = ui_->finiteTable->item(row, column);
            if (cell)
            {
                cell->setText(QString::fromStdString(turing_machine_->function(row, ui_->finiteTable->horizontalHeaderItem(column)->text().toStdString()[0])));
            }
        }
    }
    return;
}
void MainWindow::update_tape()
{
    if (middle_cell_ + 5 < turing_machine_->currentIndex() || middle_cell_ - 5 > turing_machine_->currentIndex())
    {
        middle_cell_ = turing_machine_->currentIndex();
        ui_->arrow->move(446, 4);
    }
    ui_->cell_5->setText(normalize((*turing_machine_)[middle_cell_ - 5]));
    ui_->cell_4->setText(normalize((*turing_machine_)[middle_cell_ - 4]));
    ui_->cell_3->setText(normalize((*turing_machine_)[middle_cell_ - 3]));
    ui_->cell_2->setText(normalize((*turing_machine_)[middle_cell_ - 2]));
    ui_->cell_1->setText(normalize((*turing_machine_)[middle_cell_ - 1]));
    ui_->cell0->setText(normalize((*turing_machine_)[middle_cell_]));
    ui_->cell1->setText(normalize((*turing_machine_)[middle_cell_ + 1]));
    ui_->cell2->setText(normalize((*turing_machine_)[middle_cell_ + 2]));
    ui_->cell3->setText(normalize((*turing_machine_)[middle_cell_ + 3]));
    ui_->cell4->setText(normalize((*turing_machine_)[middle_cell_ + 4]));
    ui_->cell5->setText(normalize((*turing_machine_)[middle_cell_ + 5]));
    return;
}

void MainWindow::move()
{
    QPoint pos = ui_->arrow->pos();
    int x = pos.x(), required_x = (turing_machine_->currentIndex() - middle_cell_ + 5) * 85 + 21;
    if (x < required_x)
    {
        x += 5;
    }
    if (x > required_x)
    {
        x -= 5;
        if (x < required_x)
        {
            x = required_x;
        }
    }
    ui_->arrow->move(x, pos.y());
    return;
}

void MainWindow::alert(std::string s)
{
    timer_->stop();
    alert_->setText(QString::fromStdString(s));
    alert_->exec();
    return;
}