#include "mainwindow.h"
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    ui.setupUi(this);

    actionsModel = new ActionsModel(this);
    ui.actionsTable->setModel(actionsModel);

    ui.actionNewMoveAction->setShortcut(Qt::CTRL | Qt::Key_M);

    connect(ui.actionNewMoveAction, &QAction::triggered, this, &MainWindow::newMoveAction);
    connect(ui.actionAbout, &QAction::triggered, this, [this]{ QMessageBox::about(this, tr("About"), tr("QOrder: filesystem transactions executor\n\n© Bohdan Horbeshko, 2024")); });
    connect(ui.actionAboutQt, &QAction::triggered, this, [this]{ QMessageBox::aboutQt(this); });

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

void MainWindow::newMoveAction()
{
    actionsModel->addAction(QString(""), QString(""));
    ui.actionsTable->repaint();
}
