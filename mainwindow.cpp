#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
        ui->setupUi(this);
        this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow() {
        delete ui;
}


void MainWindow::on_actionNew_triggered() {
        currentFile.clear();
        ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered() {
        //Get filename from dialog
        QString filename = QFileDialog::getOpenFileName();
        //Set file variable to selected file from dialog & Set current file to this filename
        currentFile = filename;
        QFile file(currentFile);

        //Open file for reading
        if(!file.open(QIODevice::ReadOnly | QFile::Text)) {
                QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
                return;
        }

        //Setting title to currentfile's name
        setWindowTitle(filename);
        //Text reading
        QTextStream in(&file);
        //Set text variable of the file content
        QString text = in.readAll();
        //Set windows text to read text
        ui->textEdit->setText(text);
        file.close();

}


void MainWindow::on_actionSave_triggered() {
        QString filename = QFileDialog::getSaveFileName();
        currentFile = filename;

        QFile file(currentFile);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
                return;
        }

        setWindowTitle(currentFile);

        QTextStream out(&file);

        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
}


void MainWindow::on_actionPrint_triggered() {
        QPrinter printer;
        printer.setPrinterName("Printer Name");
        QPrintDialog pdialog(&printer, this);
        if(pdialog.exec() == QDialog::Rejected) {
                QMessageBox::warning(this, "Warning", "Cannot access printer");
                return;
        }

        ui->textEdit->print(&printer);
}

void MainWindow::on_actionExit_triggered() {
        QApplication::quit();
}


void MainWindow::on_actionCopy_triggered() {
        ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered() {
        ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered() {
        ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered() {
        ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered() {
        ui->textEdit->redo();
}

