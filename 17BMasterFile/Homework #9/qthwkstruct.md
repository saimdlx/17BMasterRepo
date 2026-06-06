This markdown file contains the following:
mainwindow.h (Structure for QT Main Window Header File)
main.cpp (Structure for QT Main Files)
mainwindow.cpp (Structure for QT Main Window Implementation File)
// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: (Leave blank for user input)
// ================================================================
// Program Description:
// MainWindow Header File
// - Defines the user interface for image viewer application.
// - Manages image loading, scaling, and basic image processing.
// ================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QComboBox>
#include <QStatusBar>
#include <QImage>
#include <QAction>

// ================================================================
// Class: MainWindow
// - Central widget for displaying images and buttons
// ================================================================
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // ================================================================
    // Slots for UI Interactions:
    // - openImage(): Opens a file dialog to load an image.
    // - zoomIn()/zoomOut(): Scales the image display.
    // - setZoom(int): Scales image based on combo box selection.
    // - fitToWindow(): Adjusts image scale to fit the viewport.
    // - grayScale(): Converts the current image to grayscale.
    // - invertColors(): Inverts the colors of the current image.
    // - resetImage(): Reverts changes to the original loaded image.
    // ================================================================
    void openImage();
    void zoomIn();
    void zoomOut();
    void setZoom(int index);
    void fitToWindow();
    void grayScale();
    void invertColors();
    void resetImage();

private:
    // ================================================================
    // UI Components and State:
    // - label: Displays the image pixmap.
    // - scroll: Provides scroll bars for large images.
    // - currentImage: Stores the currently manipulated image data.
    // - originalImage: Stores the backup of the initially loaded image.
    // - scaleFactor: Current magnification level of the image.
    // ================================================================
    QLabel *label;
    QScrollArea *scroll;
    QImage currentImage;
    QImage originalImage;
    QComboBox *zoomPercentage;
    QStatusBar *statusBar;
    QPushButton *openImageButton;
    QPushButton *zoomInButton;
    QPushButton *zoomOutButton;
    QPushButton *fitToWindowButton;
    QPushButton *grayScaleButton;
    QPushButton *invertColorsButton;
    QPushButton *resetButton;
    QAction *open;
    QAction *zoomInAction;
    QAction *zoomOutAction;
    double scaleFactor = 1.0;
};

#endif // MAINWINDOW_H

// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: (Leave blank for user input)
// ================================================================
// Program Description:
// Main File
// - Initializes the Qt environment and launches the main window.
// - Handles the application event loop.
// ================================================================
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QCoreApplication::exec();
}

// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: (Leave blank for user input)
// ================================================================
// Program Description:
// Implementation of the MainWindow class.
// - Sets up the UI layout with buttons, combo boxes, and scroll areas.
// - Implements logic for image manipulation: zooming, grayscale 
//   conversion, and color inversion.
// - Connects UI signals to appropriate functional slots.
// ================================================================
#include "mainwindow.h"
#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollArea>
#include <QPushButton>
#include <QComboBox>
#include <QStatusBar>
#include <QImage>
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>

// ================================================================
// Constructor: MainWindow
// - Sets window properties and initializes UI components.
// - Establishes signal-slot connections for all interactive elements.
// - Organizes widgets into layouts and sets the central widget.
// ================================================================
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setWindowTitle("HW9A - Image Viewer Application");
    resize(500,500);

    label = new QLabel;
    scroll = new QScrollArea;
    scroll->setStyleSheet("background-color: gray;");
    scroll->setWidget(label);

    zoomPercentage = new QComboBox;
    zoomPercentage->addItem("25%");
    zoomPercentage->addItem("50%");
    zoomPercentage->addItem("75%");
    zoomPercentage->addItem("100%");
    zoomPercentage->addItem("150%");
    zoomPercentage->addItem("200%");
    connect(zoomPercentage, &QComboBox::currentIndexChanged, this, &MainWindow::setZoom);

    openImageButton = new QPushButton("Open Image File");
    zoomInButton = new QPushButton("Zoom In");
    zoomOutButton = new QPushButton("Zoom Out");
    fitToWindowButton = new QPushButton("Fit to Window");
    grayScaleButton = new QPushButton("Enable Grayscale");
    invertColorsButton = new QPushButton("Invert Colors");
    resetButton = new QPushButton("Reset Image");

    connect(openImageButton, &QPushButton::clicked, this, &MainWindow::openImage);
    connect(zoomInButton, &QPushButton::clicked, this, &MainWindow::zoomIn);
    connect(zoomOutButton, &QPushButton::clicked, this, &MainWindow::zoomOut);
    connect(fitToWindowButton, &QPushButton::clicked, this, &MainWindow::fitToWindow);
    connect(grayScaleButton, &QPushButton::clicked, this, &MainWindow::grayScale);
    connect(invertColorsButton, &QPushButton::clicked, this, &MainWindow::invertColors);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetImage);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(openImageButton);
    buttonLayout->addWidget(zoomInButton);
    buttonLayout->addWidget(zoomOutButton);
    buttonLayout->addWidget(fitToWindowButton);
    buttonLayout->addWidget(grayScaleButton);
    buttonLayout->addWidget(invertColorsButton);
    buttonLayout->addWidget(resetButton);

    statusBar = new QStatusBar(this);
    setStatusBar(statusBar);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(zoomPercentage);
    mainLayout->addWidget(scroll);



    QWidget *central = new QWidget;
    central->setLayout(mainLayout);
    setCentralWidget(central);

    open = new QAction(tr("Open File"), this);
    zoomInAction = new QAction(tr("&Zoom In"), this);
    zoomOutAction = new QAction(tr("&Zoom Out"), this);
    open->setShortcut(QKeySequence::Open);
    zoomInAction->setShortcut(QKeySequence::ZoomIn);
    zoomOutAction->setShortcut(QKeySequence::ZoomOut);
    addAction(open);
    addAction(zoomInAction);
    addAction(zoomOutAction);
    connect(zoomInAction, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(zoomOutAction, &QAction::triggered, this, &MainWindow::zoomOut);
    connect(open, &QAction::triggered,this, &MainWindow::openImage);
}

MainWindow::~MainWindow() = default;

// ================================================================
// Function: openImage
// - Launches a file dialog for image selection.
// - Loads the chosen image into memory and displays it.
// - Updates window title and status bar with image metadata.
// ================================================================
void MainWindow::openImage(){
    QString fileName = QFileDialog::getOpenFileName(this,
    tr("Open Image"),
    QString(),
    tr("Image Files (*.png *.jpg *.bmp *.gif)"));

    if (fileName.isEmpty()){
        return;
    }

    currentImage = QImage(fileName);
    if (currentImage.isNull()){
        QMessageBox::critical(this, tr("Error!"), tr("Unable to load image!"));
        return;
    }
    originalImage = currentImage;
    label->setPixmap(QPixmap::fromImage(currentImage));
    label->adjustSize();

    setWindowTitle(fileName + "-" + QString::number(currentImage.width()) + " x " + QString::number(currentImage.height()));
    statusBar->showMessage("Loaded " + fileName + "-" + QString::number(currentImage.width()) + " x " + QString::number(currentImage.height()));
}

// ================================================================
// Function: zoomIn
// - Increases the scale factor by 25%.
// - Updates the image display based on the new scale.
// ================================================================
void MainWindow::zoomIn(){
    scaleFactor *= 1.25;
    QSize newSize = currentImage.size() * scaleFactor;
    QPixmap pix = QPixmap::fromImage(currentImage);
    pix = pix.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pix);
    label->resize(newSize);
}

// ================================================================
// Function: zoomOut
// - Decreases the scale factor by 20% (multiplies by 0.8).
// - Updates the image display based on the new scale.
// ================================================================
void MainWindow::zoomOut(){
    scaleFactor *= 0.8;
    QSize newSize = currentImage.size() * scaleFactor;
    QPixmap pix = QPixmap::fromImage(currentImage);
    pix = pix.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pix);
    label->resize(newSize);
}

// ================================================================
// Function: setZoom
// - Sets the scale factor based on the selected index in the 
//   zoomPercentage combo box.
// - Refreshes the image display to match the chosen percentage.
// ================================================================
void MainWindow::setZoom(int index){
    switch(index){
    case 0:
        scaleFactor = 0.25;
        break;
    case 1:
        scaleFactor = 0.50;
        break;
    case 2:
        scaleFactor = 0.75;
        break;
    case 3:
        scaleFactor = 1.00;
        break;
    case 4:
        scaleFactor = 1.50;
        break;
    case 5:
        scaleFactor = 2.00;
        break;
    }
    QSize newSize = currentImage.size() * scaleFactor;
    QPixmap pix = QPixmap::fromImage(currentImage);
    pix = pix.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pix);
    label->resize(newSize);
}

// ================================================================
// Function: fitToWindow
// - Calculates the scale factor needed to fit the image within
//   the current scroll area viewport.
// - Re-renders the image at the calculated scale.
// ================================================================
void MainWindow::fitToWindow(){
    if (currentImage.isNull()) return;
    QSize viewportSize = scroll->viewport()->size();
    double factorX = (double)viewportSize.width() / currentImage.width();
    double factorY = (double)viewportSize.height() / currentImage.height();
    scaleFactor = qMin(factorX, factorY);

    QSize newSize = currentImage.size() * scaleFactor;
    QPixmap pix = QPixmap::fromImage(currentImage);
    pix = pix.scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pix);
    label->resize(newSize);
}

// ================================================================
// Function: grayScale
// - Iterates through every pixel of the current image.
// - Calculates the grayscale value and updates the pixel.
// - Refreshes the display to show the grayscale effect.
// ================================================================
void MainWindow::grayScale() {
    if (currentImage.isNull()) return;
    for (int y = 0; y < currentImage.height(); y++) {
        for (int x = 0; x < currentImage.width(); x++) {
            QRgb pixel = currentImage.pixel(x, y);
            int gray = qGray(pixel);
            currentImage.setPixel(x, y, qRgba(gray, gray, gray, qAlpha(pixel)));
        }
    }
    QSize newSize = currentImage.size() * scaleFactor;
    label->setPixmap(QPixmap::fromImage(currentImage).scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// ================================================================
// Function: invertColors
// - Iterates through every pixel of the current image.
// - Subtracts each color component from 255 to invert it.
// - Refreshes the display to show the inverted effect.
// ================================================================
void MainWindow::invertColors() {
    if (currentImage.isNull()) return;
    for (int y = 0; y < currentImage.height(); y++) {
        for (int x = 0; x < currentImage.width(); x++) {
            QRgb pixel = currentImage.pixel(x, y);
            currentImage.setPixel(x, y, qRgba(255 - qRed(pixel), 255 - qGreen(pixel), 255 - qBlue(pixel), qAlpha(pixel)));
        }
    }
    QSize newSize = currentImage.size() * scaleFactor;
    label->setPixmap(QPixmap::fromImage(currentImage).scaled(newSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

// ================================================================
// Function: resetImage
// - Restores currentImage to originalImage (the state at load).
// - Resets scale factor to 1.0 and updates UI selection.
// ================================================================
void MainWindow::resetImage() {
    if (originalImage.isNull()) return;
    currentImage = originalImage;
    scaleFactor = 1.0;
    zoomPercentage->setCurrentIndex(3); // 100%
    label->setPixmap(QPixmap::fromImage(currentImage));
    label->adjustSize();
}