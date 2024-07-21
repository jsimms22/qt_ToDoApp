#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // open a file in the current working directory
    QFile file(this->m_path);

    if (!file.open(QIODevice::ReadWrite)) {
        // 0 refers to the parent window, our MainWindow
        // "error" is the name of the error box
        // file.errorString() is our output to the box
        QMessageBox::information(0,"error",file.errorString());
        /* to do: handle errors */
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        // iterate over lines of our save file and write to our list widget
        QString line = file.readLine();
        auto item = new QListWidgetItem(line, ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    file.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    // objects with parents derived from QObject will be deleted when the parent is deleted
    if (ui->txtAddTask->text().length() != 0) {
        auto item = new QListWidgetItem(ui->txtAddTask->text(), ui->listWidget);
        // we assign parent of item to our list widget
        ui->listWidget->addItem(item);
        // set flag below allows our list items to become editable
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        // remove text from prompt window
        ui->txtAddTask->clear();
        // reassign focus to prompt window
        ui->txtAddTask->setFocus();
    }
}

// We can allow multi-select under our widget options in ui design
void MainWindow::on_btnRemove_clicked()
{
    for (auto item : ui->listWidget->selectedItems()) {
        delete item;
    }
}


void MainWindow::on_btnRemoveAll_clicked()
{
    // initialize item and take first item in list
    auto item = ui->listWidget->takeItem(0);
    while (item) {
        // delete items while item != nullptr
        delete item;
        item = ui->listWidget->takeItem(0);
    }
}

void MainWindow::on_btnSave_clicked()
{
    // deletes old file if its exists
    // returns true if deleted
    QFile::remove(this->m_path);

    // open new file with same name
    QFile file(this->m_path);
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(0,"error",file.errorString());
    }

    // write out contents of list widget to file
    QTextStream out(&file);
    for (size_t i = 0; i < ui->listWidget->count(); ++i) {
        out << ui->listWidget->item(i)->text() << '\n';
    }

    file.close();
}

