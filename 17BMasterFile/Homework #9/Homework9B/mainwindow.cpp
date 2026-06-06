// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW9B - Main Window Class Implementation File
// ================================================================
// Program Description:
// Implementation of the MainWindow class.
// - Sets up the UI layout with drawing canvas, controls, and toolbar elements.
// - Implements logic for user interactions. Color, stroke size and styel,
//   and file management.
// - Connects UI signals to slots.
// ================================================================
#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QStatusBar>
#include <QDir>
#include <QStandardPaths>

// ================================================================
// Constructor: MainWindow
// - Initializes window properties, layout, and UI components.
// - Sets up timer for auto-saving and establishes signal-slot connections.
// ================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), currentColor(Qt::black) {
    setWindowTitle("HW9B - Drawing Canvas Application");
    resize(800, 600);

    canvas = new DrawingCanvas(this);

    colorButton = new QPushButton("Choose Color", this);
    saveButton = new QPushButton("Save", this);
    openButton = new QPushButton("Open", this);
    newButton = new QPushButton("New", this);
    
    widthSlider = new QSlider(Qt::Horizontal, this);
    widthSlider->setRange(1, 20);
    widthSlider->setValue(2);
    widthLabel = new QLabel("Width: 2", this);
    
    styleComboBox = new QComboBox(this);
    styleComboBox->addItem("Solid");
    styleComboBox->addItem("Dashed");
    styleComboBox->addItem("Dotted");
    styleComboBox->addItem("Dash-Dot");
    
    colorPreview = new QLabel(this);
    colorPreview->setFixedSize(20, 20);
    updateColorPreview();

    autoSaveCheckBox = new QCheckBox("Auto-save (60s)", this);
    
    autoSaveTimer = new QTimer(this);
    autoSaveTimer->setInterval(60000); // 60 seconds

    QHBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->addWidget(newButton);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(saveButton);
    controlLayout->addWidget(colorButton);
    controlLayout->addWidget(colorPreview);
    controlLayout->addWidget(new QLabel("Width:", this));
    controlLayout->addWidget(widthSlider);
    controlLayout->addWidget(widthLabel);
    controlLayout->addWidget(new QLabel("Style:", this));
    controlLayout->addWidget(styleComboBox);
    controlLayout->addWidget(autoSaveCheckBox);
    controlLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(canvas, 1);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
    
    statusBar()->showMessage("Ready");

    // Connections
    connect(colorButton, &QPushButton::clicked, this, &MainWindow::chooseColor);
    connect(widthSlider, &QSlider::valueChanged, this, &MainWindow::changePenWidth);
    connect(styleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::changePenStyle);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(openButton, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(newButton, &QPushButton::clicked, this, &MainWindow::newCanvas);
    connect(autoSaveCheckBox, &QCheckBox::stateChanged, this, &MainWindow::toggleAutoSave);
    connect(autoSaveTimer, &QTimer::timeout, this, &MainWindow::autoSave);
}

MainWindow::~MainWindow() = default;

// ================================================================
// Function: chooseColor
// - Opens a QColorDialog for the user to select a new pen color.
// - Updates the canvas settings and the UI color preview label.
// ================================================================
void MainWindow::chooseColor() {
    QColor newColor = QColorDialog::getColor(currentColor, this, "Choose Pen Color");
    if (newColor.isValid()) {
        currentColor = newColor;
        canvas->setPenColor(currentColor);
        updateColorPreview();
    }
}

// ================================================================
// Function: updateColorPreview
// - Updates the style sheet of the color preview label to visually
//   display the currently selected pen color.
// ================================================================
void MainWindow::updateColorPreview() {
    QString style = QString("background-color: %1; border: 1px solid black;").arg(currentColor.name());
    colorPreview->setStyleSheet(style);
}

// ================================================================
// Function: changePenWidth
// - Updates the canvas pen width based on the provided value.
// - Modifies the width label text to reflect the new width.
// ================================================================
void MainWindow::changePenWidth(int width) {
    canvas->setPenWidth(width);
    widthLabel->setText(QString("Width: %1").arg(width));
}

// ================================================================
// Function: changePenStyle
// - Updates the canvas pen style depending on the combo box selection.
// - Maps UI dropdown indices to Qt::PenStyle enumerations.
// ================================================================
void MainWindow::changePenStyle(int index) {
    Qt::PenStyle style = Qt::SolidLine;
    switch (index) {
        case 0: style = Qt::SolidLine; break;
        case 1: style = Qt::DashLine; break;
        case 2: style = Qt::DotLine; break;
        case 3: style = Qt::DashDotLine; break;
    }
    canvas->setPenStyle(style);
}

// ================================================================
// Function: saveFile
// - Opens a save dialog to let the user save the current canvas drawing.
// - Notifies the user via the status bar upon success or shows an error.
// ================================================================
void MainWindow::saveFile() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save Image", QString(), "Images (*.png *.jpg)");
    if (!fileName.isEmpty()) {
        if (canvas->saveImage(fileName)) {
            statusBar()->showMessage(QString("Saved to %1").arg(fileName), 3000);
        } else {
            QMessageBox::warning(this, "Save Error", "Failed to save the image.");
        }
    }
}

// ================================================================
// Function: openFile
// - Prompts to save unsaved changes if the current canvas is modified.
// - Opens a dialog for selecting an image file to load onto the canvas.
// ================================================================
void MainWindow::openFile() {
    if (canvas->isModified()) {
        QMessageBox::StandardButton res = QMessageBox::question(this, "Save changes?","The canvas has been modified.\nDo you want to save your changes?", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (res == QMessageBox::Save) {
            saveFile();
        } else if (res == QMessageBox::Cancel) {
            return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", QString(), "Images (*.png *.jpg *.bmp)");
    if (!fileName.isEmpty()) {
        if (canvas->loadImage(fileName)) {
            statusBar()->showMessage(QString("Loaded %1").arg(fileName), 3000);
        } else {
            QMessageBox::warning(this, "Open Error", "Failed to load the image.");
        }
    }
}

// ================================================================
// Function: newCanvas
// - Prompts to save unsaved changes before clearing the active canvas.
// - Clears the current drawing to provide a blank surface.
// ================================================================
void MainWindow::newCanvas() {
    if (canvas->isModified()) {
        QMessageBox::StandardButton res = QMessageBox::question(this, "Save changes?","The canvas has been modified.\nDo you want to save your changes?",QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (res == QMessageBox::Save) {
            saveFile();
        } else if (res == QMessageBox::Cancel) {
            return;
        }
    }
    canvas->clearCanvas();
}

// ================================================================
// Function: toggleAutoSave
// - Enables or disables the autoSaveTimer based on checkbox state.
// ================================================================
void MainWindow::toggleAutoSave(int state) {
    if (state == Qt::Checked) {
        autoSaveTimer->start();
    } else {
        autoSaveTimer->stop();
    }
}

// ================================================================
// Function: autoSave
// - Automatically saves the canvas to a temporary background file.
// - Triggers periodically.
// ================================================================
void MainWindow::autoSave() {
    QString tempPath = QDir::tempPath() + QDir::separator() + "autosave_canvas.png";
    if (canvas->saveImage(tempPath, false)) {
        statusBar()->showMessage(QString("Auto-saved to %1").arg(tempPath), 3000);
    }
}
