#include "bulls_and_cows.h"
#include "ui_bulls_and_cows.h"
#include <QDateTime>
#include <QDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QRandomGenerator>

bulls_and_cows::bulls_and_cows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::bulls_and_cows)
{
    victory = false;

    ui->setupUi(this);
    setWindowFlags(Qt::Widget| Qt::MSWindowsFixedSizeDialogHint);
    ui->leGuess->setValidator(new QRegExpValidator(QRegExp("[0-9]{4}")));

    recordsWindow = new Record();
}

bulls_and_cows::~bulls_and_cows()
{
    delete ui;
}


void bulls_and_cows::on_pbNewGame_clicked()
{
    if (number.size() == 0 || victory) {
        number.resize(4);
        ui->leGuess->setEnabled(true);

    } else if (QMessageBox::No == QMessageBox::question(this,"Хм??","Вы уверены что хотите сдатся и начать заново?", QMessageBox::Yes | QMessageBox::No)) {
        return;
    }

    qsrand(QDateTime::currentDateTime().toTime_t());
    QChar tmp;
    number.clear();
    while(number.size() < 4){
        tmp = (qrand() % 10) + 48;
        if(!number.contains(tmp)){
            number.append(tmp);
        }
    }
    ui->label->setText("Игра началась");
//    QString res = QString("Игра началась %1").arg(number);
//    ui->label->setText(res);
    ui->leGuess->clear();
    ui->twResults->setRowCount(0);
    victory = false;
}

void bulls_and_cows::on_pbChek_clicked()
{
    ui->pbChek->setEnabled(false);
    QString current = ui->leGuess->text();
    if(current.size() != 4){
        QMessageBox::warning(this,"Ошибка","Введите 4 цифры");
        return;
    }
    QPair<int, int> pair = analyse(number, current);
    QString result = QString("%1 быков, %2 коров").arg(pair.first).arg(pair.second);
    ui->twResults->insertRow(ui->twResults->rowCount());
    ui->twResults->setItem(ui->twResults->rowCount()-1,0,new QTableWidgetItem(current));
    ui->twResults->setItem(ui->twResults->rowCount()-1,1,new QTableWidgetItem(result));
    ui->twResults->scrollToBottom();
    victory = pair.first == 4;
    if (victory) {
        completeGame();
    } else {
        ui->label->setText("Не угадали, пробуйте еще");
    }
}

void bulls_and_cows::completeGame()
{
    int res = ui->twResults->rowCount();
    if (res < recordsWindow->getMinRecord()) {
        bool okClicked;
        QString name = QInputDialog::getText(this, tr("Новый рекорд"), tr("Имя:"), QLineEdit::Normal, "anonimus", &okClicked);
        if (okClicked && !name.isEmpty()) {
            recordsWindow->saveNewResult(res, name);
        }
    } else {
        QMessageBox::warning(this, "Победа!", "Поздравляем, вы угадали");
    }
    ui->label->setText("Игра закончена");
    ui->leGuess->setEnabled(false);
}

QPair<int,int> bulls_and_cows::analyse(QString res, QString guess)
{
    QPair<int,int> pair = qMakePair(0,0);
    for (int i=0; i < 4; i++) {
        if (res[i] == guess[i]) {
            pair.first++;
            guess[i] = '*';
            res[i] = '*';
        }
    }
    for (int i=0; i < 4; i++) {
        if (guess[i] == '*') {
            continue;
        }
        int n = res.indexOf(guess[i]);
        if (n != -1) {
            pair.second++;
            res[n] = '*';
        }
    }
    return pair;
}

void bulls_and_cows::on_leGuess_textChanged(const QString &arg1)
{
    ui->pbChek->setEnabled(!ui->leGuess->text().isEmpty());
}

void bulls_and_cows::on_pbRecords_clicked()
{
    recordsWindow->show();
}
