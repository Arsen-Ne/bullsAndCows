#include "record.h"
#include "ui_record.h"

#include <QFile>

Record::Record(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Record)
{
    ui->setupUi(this);    
    readMap();
    updateTable();
}

void Record::readMap()
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
            QDataStream str(&file);
            str >> resultsMap;
    }
    file.close();
}

void Record::saveMap()
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream str(&file);
        str << resultsMap;
    }
    file.close();
}

void Record::updateTable() {
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setRowCount(resultsMap.size());
    int row = 0;
    for(auto it = resultsMap.begin(); it != resultsMap.end(); it++) {
        ui->tableWidget->setItem(row,0,new QTableWidgetItem(QString::number(it.key())));
        ui->tableWidget->setItem(row,1,new QTableWidgetItem(it.value()));
        row++;
    }
}

Record::~Record()
{
    delete ui;
}

void Record::saveNewResult(int res, QString name)
{
    resultsMap.insert(res, name);
    if (resultsMap.size() > 10) {
        auto it = resultsMap.end();
        it--;
        resultsMap.remove(it.key(), it.value());
    }
    updateTable();
    saveMap();
}

int Record::getMinRecord() const
{
    return (resultsMap.size() < 10) ? INT_MAX : resultsMap.lastKey();
}
