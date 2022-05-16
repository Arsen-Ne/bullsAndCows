#ifndef RECORD_H
#define RECORD_H

#include <QMainWindow>
#include <QMultiMap>

namespace Ui {
class Record;
}

class Record : public QMainWindow
{
    Q_OBJECT

public:
    explicit Record(QWidget *parent = nullptr);
    ~Record();
    void saveNewResult(int, QString);
    int getMinRecord() const;

private:
    Ui::Record *ui;
    QMultiMap<int, QString> resultsMap;
    const QString fileName = "records";
    void readMap();
    void saveMap();
    void updateTable();
};

#endif // RECORD_H
