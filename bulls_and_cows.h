#ifndef BULLS_AND_COWS_H
#define BULLS_AND_COWS_H

#include "record.h"

#include <QMainWindow>
#include <QRandomGenerator>

QT_BEGIN_NAMESPACE
namespace Ui { class bulls_and_cows; }
QT_END_NAMESPACE

class bulls_and_cows : public QMainWindow
{
    Q_OBJECT

public:
    bulls_and_cows(QWidget *parent = nullptr);
    ~bulls_and_cows();

private slots:
    void on_pbNewGame_clicked();

    void on_pbChek_clicked();

    void on_leGuess_textChanged(const QString &arg1);

    void on_pbRecords_clicked();

private:
    Ui::bulls_and_cows *ui;    
    Record *recordsWindow;
    QString number;
    bool victory;
    QPair<int,int> analyse(QString, QString);
    void completeGame();
};
#endif // BULLS_AND_COWS_H
