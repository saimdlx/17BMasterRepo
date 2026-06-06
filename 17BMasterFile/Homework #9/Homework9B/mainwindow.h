// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW9B - Main Window Header File
// ================================================================
// Program Description:
// Main Window Header File
// - Defines the main application window and UI controls.
// - Manages canvas interactions, tool configurations, and file saving/loading.
// ================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QTimer>
#include "drawingcanvas.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    // ================================================================
    // Slots for UI Interactions:
    // - chooseColor(): Opens a color dialog to select a pen color.
    // - changePenWidth(int): Updates the pen width based on slider value.
    // - changePenStyle(int): Updates the pen style based on combo box selection.
    // - saveFile(): Opens a file dialog to save the current canvas drawing.
    // - openFile(): Opens a file dialog to load an image into the canvas.
    // - newCanvas(): Clears the current canvas to start a new drawing.
    // - autoSave(): Automatically saves a temporary copy of the canvas.
    // - toggleAutoSave(int): Enables or disables the auto-save timer.
    // ================================================================
    void chooseColor();
    void changePenWidth(int width);
    void changePenStyle(int index);
    void saveFile();
    void openFile();
    void newCanvas();
    void autoSave();
    void toggleAutoSave(int state);

private:
    void updateColorPreview();
    
    // ================================================================
    // UI Components:
    // - canvas: The central drawing widget.
    // - colorButton, saveButton, openButton, newButton: UI action buttons.
    // - widthSlider, widthLabel: Controls and displays the pen width.
    // - styleComboBox: Dropdown for selecting pen style.
    // - colorPreview: Label showing the currently selected pen color.
    // - autoSaveCheckBox: Toggles the auto-save feature.
    // - autoSaveTimer: Timer to trigger periodic auto-saves.
    // - currentColor: Stores the current drawing color.
    // ================================================================
    DrawingCanvas *canvas;
    QPushButton *colorButton;
    QPushButton *saveButton;
    QPushButton *openButton;
    QPushButton *newButton;
    QSlider *widthSlider;
    QLabel *widthLabel;
    QComboBox *styleComboBox;
    QLabel *colorPreview;
    QCheckBox *autoSaveCheckBox;
    QTimer *autoSaveTimer;
    QColor currentColor;
};

#endif