#ifndef REPLACEWIDGET_H
#define REPLACEWIDGET_H
#include "notepad.h"

#include <QWidget>
class QLineEdit;

class ReplaceWidget : public QWidget
{
    Q_OBJECT
public:
    ReplaceWidget(QWidget *parent = 0);

signals:
    void clicked();

public slots:
    void replace();


public:
    QString getReplaceWord();
    QString getFindWord();
    bool okpress();

private:
    QLineEdit* lineEdit1;
    QLineEdit* lineEdit2;
    QString m_findWord;
    QString m_replaceWord;
    bool okPressed ;


};

#endif // REPLACEWIDGET_H
