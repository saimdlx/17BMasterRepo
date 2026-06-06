// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: Image Viewer Application Header File
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