#include "notepad.h"

#include <QMenu>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QFileDialog>
#include <QFontDialog>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>
#include <QPushButton>
#include <QTextCursor>
#include <QPoint>
#include <QMouseEvent>
#include <QTextEdit>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialog>
#include <QColorDialog>
#include <QKeySequence>
#include <QStyle>

Notepad::Notepad(QWidget *parent) :
    QMainWindow(parent)
{
    m_openedFileName = " ";

    QMenu* fileMenu = new QMenu("File");
    QMenu* helpMenu = new QMenu("Help");
    QMenu* editMenu = new QMenu("Edit");
    QMenu* formatMenu = new QMenu("Format");

    QAction* newAction = fileMenu->addAction("New");
    newAction->setShortcut(QKeySequence("Ctrl+N"));

    QAction* openAction = fileMenu->addAction("Open");
    openAction->setShortcut(QKeySequence("Ctrl+O"));

    QAction* saveAction = fileMenu->addAction("Save");
    saveAction->setShortcut(QKeySequence("Ctrl+S"));

    QAction* saveAsAction = fileMenu->addAction("Save As");
    QAction* exitAction = fileMenu->addAction("Exit");

    QAction* undoAction = editMenu->addAction("Undo");
    undoAction->setShortcut((QKeySequence("Ctrl+Z")));

    QAction* cutAction = editMenu->addAction("Cut");
    cutAction->setShortcut(QKeySequence("Ctrl+X"));

    QAction* copyAction = editMenu->addAction("Copy");
    copyAction->setShortcut(QKeySequence("Ctrl+C"));

    QAction* pasteAction = editMenu->addAction("Paste");
    pasteAction->setShortcut(QKeySequence("Ctrl+V"));

    QAction* replaceAction = editMenu->addAction("Replace");
    replaceAction->setShortcut(QKeySequence("Ctrl+H"));

    QAction* selectALLAaction = editMenu->addAction("Select all");
    selectALLAaction->setShortcut(QKeySequence("Ctrl+A"));

    QAction* fontAction = formatMenu->addAction("Font");

    QAction* aboutAction = helpMenu->addAction("About Us");

    this->menuBar()->addMenu(fileMenu);
    this->menuBar()->addMenu(editMenu);
    this->menuBar()->addMenu(formatMenu);
    this->menuBar()->addMenu(helpMenu);

    textEdit = new QTextEdit;
    this->setCentralWidget(textEdit);

    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(reSaveFile()));
    connect(exitAction, SIGNAL(triggered()),this,SLOT(close()));

    connect(undoAction, SIGNAL(triggered()), textEdit, SLOT(undo()));
    connect(cutAction, SIGNAL(triggered()), textEdit, SLOT(cut()));
    connect(copyAction, SIGNAL(triggered()), textEdit, SLOT(copy()));
    connect(pasteAction, SIGNAL(triggered()), textEdit, SLOT(paste()));
    connect(replaceAction, SIGNAL(triggered()), this, SLOT(replaceClicked()));
    connect(selectALLAaction, SIGNAL(triggered()), textEdit, SLOT(selectAll()));

    connect(fontAction, SIGNAL(triggered()), this, SLOT(changeFont()));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutUs()));
}

void Notepad::openFile()
{
    m_openedFileName = QFileDialog::getOpenFileName(0,"Files List","c:/","Text(*.txt)");
    qDebug() <<m_openedFileName;
    QFile file(m_openedFileName);
    bool opened = file.open(QFile::ReadOnly);

    if(opened)
    {
        m_contents = QString(file.readAll());
        textEdit->setPlainText(m_contents);
    }
}

void Notepad::saveFile()
{
    m_contents = textEdit->toPlainText();
    m_fileName = QFileDialog::getSaveFileName(0,"Save Files", "C:/","text(*.txt)");
    QFile file(m_fileName);
    bool opened = file.open(QFile::WriteOnly);

    if(opened)
    {
        file.write(m_contents.toAscii());
        file.flush();
        file.close();
    }
}

void Notepad::newFile()
{
    if(textEdit->toPlainText()== NULL)
    {
        textEdit->clear();
    }
    else
    {
        m_contents = textEdit->toPlainText();
        m_msgBox = new QMessageBox;
        m_msgBox->setText("Do you want to save changes?");

        QPushButton* pb1 = m_msgBox->addButton("Save", QMessageBox::AcceptRole);
        QPushButton* pb2 = m_msgBox->addButton("Don't Save", QMessageBox::RejectRole);
        QPushButton* pb3 = m_msgBox->addButton("Cancel",QMessageBox::NoRole);

        m_msgBox->exec();
        if(m_msgBox->clickedButton()==pb1)
        {
            m_fileName = QFileDialog::getSaveFileName(0,"Save File","c:/");
            QFile file(m_fileName);
            bool opened = file.open(QFile::WriteOnly);
            if(opened)
            {
                file.write(m_contents.toAscii());
                file.flush();
                file.close();
            }
        }
        else if(m_msgBox->clickedButton()==pb3)
        {
            textEdit->setPlainText(m_contents);
        }
        else if(m_msgBox->clickedButton()==pb2)
        {
            textEdit->clear();
        }
    }
}

void Notepad::reSaveFile()
{
    if(m_openedFileName== " ")
    {
        m_contents = textEdit->toPlainText();
        m_fileName = QFileDialog::getSaveFileName(this,"Save File","c:/","Text(*.txt)");
        QFile file(m_fileName);
        bool opened = file.open(QFile::ReadWrite);
        if(opened)
        {
            file.write(m_contents.toAscii());
            file.flush();
            file.close();
        }
    }
    else
    {
        m_contents = textEdit->toPlainText();
        m_msgBox1 = new QMessageBox;
        m_msgBox1->setText("Do ou want to save the changes ?");
        QPushButton* pb1 = m_msgBox1->addButton("Save",QMessageBox::AcceptRole);
        QPushButton* pb2 = m_msgBox1->addButton("Don't Save",QMessageBox::RejectRole);
        QPushButton* pb3 = m_msgBox1->addButton("Cancel", QMessageBox::NoRole);
        m_msgBox1->exec();

        if(m_msgBox1->clickedButton()==pb1)
        {
            QFile file(m_openedFileName);
            file.flush();
            m_contents = textEdit->toPlainText();

            bool opened = file.open(QFile::ReadWrite);
            if(opened)
            {
                file.write(m_contents.toAscii());
                file.flush();
                file.close();
            }
            this->close();
        }
        else if(m_msgBox1->clickedButton()==pb2)
        {
            textEdit->close();
        }
        else if(m_msgBox1->clickedButton()==pb3)
        {
            textEdit->setPlainText(m_contents);
        }
    }
}


void Notepad::aboutUs()
{
    m_fileName = "C:/Qt/4.7.3/LICENSE";
    QFile file(m_fileName);
    bool opened = file.open(QFile::ReadOnly);
    if(opened)
    {
        m_contents = QString(file.readAll());
        textEdit->setPlainText(m_contents);
    }
}

void Notepad::changeFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, QFont("Helvetica [Cronyx]", 10), this);
    if(ok)
        textEdit->setFont(font);
}

void Notepad::replaceClicked()
{
    m_contents = textEdit->toPlainText();
    QDialog replaceDialog(this);

    QLabel* label1 = new QLabel("Find Word :");
    QLabel* label2 = new QLabel("Replace Word");

    QLineEdit* le1 = new QLineEdit;
    QLineEdit* le2 = new QLineEdit;

    QPushButton* pb1 = new QPushButton("OK");
    QPushButton* pb2 = new QPushButton("Cancel");

    QHBoxLayout* hLayout1 = new QHBoxLayout;
    QHBoxLayout* hLayout2 = new QHBoxLayout;
    QHBoxLayout* hLayout3 = new QHBoxLayout;

    QVBoxLayout* vLayout = new QVBoxLayout;

    hLayout1->addWidget(label1);
    hLayout1->addWidget(le1);

    hLayout2->addWidget(label2);
    hLayout2->addWidget(le2);

    hLayout3->addWidget(pb1);
    hLayout3->addWidget(pb2);

    replaceDialog.setLayout(vLayout);
    vLayout->addLayout(hLayout1);
    vLayout->addLayout(hLayout2);
    vLayout->addLayout(hLayout3);

    connect(pb1, SIGNAL(pressed()), &replaceDialog, SLOT(accept()));
    connect(pb2, SIGNAL(released()), &replaceDialog, SLOT(reject()));
    replaceDialog.exec();

    if(replaceDialog.exec()== QDialog::Accepted)
    {
        m_contents.replace(le1->text(),le2->text());
        textEdit->setText(m_contents);
    }
}
