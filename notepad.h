#ifndef NOTEPAD_H
#define NOTEPAD_H


#include <QMainWindow>
#include <QMouseEvent>
#include <QPoint>

class QTextEdit;
class QMessageBox;
class ReplaceWidget;

class Notepad : public QMainWindow
{
    Q_OBJECT
public:
    Notepad(QWidget *parent = 0);

signals:

public slots:
    void openFile();
    void saveFile();
    void newFile();
    void reSaveFile();
    void aboutUs();
    void changeFont();
    void replaceClicked();

private:
    QString m_fileName;
    QTextEdit* textEdit;
    QString m_contents;
    QMessageBox* m_msgBox;
    QMessageBox* m_msgBox1;
    QString m_openedFileName;

};
#endif // NOTEPAD_H
