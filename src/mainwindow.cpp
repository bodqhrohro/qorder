#include "mainwindow.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.sourceDirButton, &QPushButton::clicked, this, [=]{ MainWindow::directoryDialog(SOURCE_DIR); });
    connect(ui.targetDirButton, &QPushButton::clicked, this, [=]{ MainWindow::directoryDialog(TARGET_DIR); });
}

void MainWindow::directoryDialog(dirType type)
{
    QLineEdit* dirEdit;
    QString title;
    switch (type) {
        case SOURCE_DIR:
            dirEdit = ui.sourceDir;
            title = tr("Choose the source directory");
        break;
        case TARGET_DIR:
            dirEdit = ui.targetDir;
            title = tr("Choose the target directory");
        break;
    }

    QString newPath = QFileDialog::getExistingDirectory(this,
                                                        title,
                                                        dirEdit->text(),
                                                        QFileDialog::ShowDirsOnly);
    if (newPath != "") {
        dirEdit->setText(newPath);
    }
}
