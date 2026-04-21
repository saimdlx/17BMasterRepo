# HW #

# Advanced Qt Widgets & Multimedia

## Homework Assignment 1: Image Viewer Application

## Objective

Build a fully functional Image Viewer application that demonstrates your understanding of
QFileDialog, QPixmap, QImage, QLabel, and widget layout. The viewer should allow the user to
open images, zoom in and out, and apply basic image effects.

## Requirements

#### Part A: Core Image Viewing

1. Create a main window with a QLabel inside a QScrollArea to display images.
2. Add an "Open Image" button (or File menu) that uses QFileDialog::getOpenFileName()
    to let the user select an image file (support PNG, JPG, BMP, GIF).
3. Display the selected image in the QLabel using QPixmap.
4. Show the image filename and dimensions in the window title (e.g., "photo.jpg — 1920 x
    1080").
5. If the file fails to load, show a QMessageBox::critical() error.

#### Part B: Zoom Controls

6. Add "Zoom In" and "Zoom Out" buttons.
7. Zoom In should scale the image by 125% each time it is clicked.
8. Zoom Out should scale the image by 80% each time it is clicked.
9. Add a "Fit to Window" button that scales the image to fit the current window size while
    preserving the aspect ratio.


#### Part C: Image Effects

10. Add a "Grayscale" button that converts the image to grayscale using QImage pixel
    manipulation. Display the result.
11. Add a "Invert Colors" button that inverts all pixel colors (255 - R, 255 - G, 255 - B).
    Display the result.
12. Add a "Reset" button that restores the original image (un-modified).

#### Part D: User Experience

13. Add a QComboBox or buttons to select the zoom percentage (25%, 50%, 75%, 100%,
    150%, 200%).
14. Show a status bar message when an image is loaded (e.g., "Loaded photo.jpg — 1920 x
    1080").
15. Use alternating background color or styling for the scroll area to distinguish it from the
    image.
16. Add keyboard shortcuts: Ctrl+O for Open, Ctrl+Plus for Zoom In, Ctrl+Minus for Zoom
    Out.


# Sample output:

**(Image Viewer)** shows the complete application with the toolbar (Open, Zoom In/Out, Fit to
Window, zoom percentage dropdown, Grayscale, Invert, Reset), a loaded sunset image
displayed in the scroll area, the window title showing the filename and dimensions, and the

# status bar confirming the load.


## Homework Assignment 2: Drawing Canvas

## Application

### Objective

Build a Drawing Canvas application that demonstrates your understanding of QPainter, mouse
events, QColorDialog, QTimer, and custom widget creation. The application should allow the
user to draw freehand, choose colors, adjust pen width, and save their artwork.

### Requirements

#### Part A: Drawing Canvas Widget

17. Create a custom QWidget subclass called DrawingCanvas that stores drawing data on a
    QImage.
18. Implement mousePressEvent(), mouseMoveEvent(), and mouseReleaseEvent() to
    support freehand drawing.
19. Use QPainter to draw lines between consecutive mouse positions (as shown in the
    lecture example).
20. Override paintEvent() to display the QImage canvas on screen.
21. Add a clearCanvas() method that fills the QImage with white and calls update().

#### Part B: Color and Pen Controls

22. Add a "Choose Color" button that opens QColorDialog::getColor() and sets the pen
    color.
23. Add a QSlider (range 1–20) to control the pen width. Show the current width in a QLabel.
24. Add a QComboBox to select the pen style: Solid, Dashed, Dotted, Dash-Dot.
25. Display a small preview rectangle showing the current pen color (e.g., a QLabel with a
    colored background).

#### Part C: File Operations

26. Add a "Save" button that uses QFileDialog::getSaveFileName() to save the canvas as a
    PNG or JPG file (use QImage::save()).
27. Add an "Open" button that loads an image into the canvas using QImage::load().
28. Show a QMessageBox::question() confirmation ("Save changes?") when the user clicks
    "New" (clear canvas) if the canvas has been modified.


#### Part D: Timer-Based Feature

29. Add an auto-save feature using QTimer that saves the canvas to a temporary file every
    60 seconds.
30. Show a brief status bar notification ("Auto-saved") each time the auto-save triggers.
31. Add a QCheckBox to enable/disable the auto-save timer.
32. When the auto-save timer fires, save to a fixed temporary path (e.g.,
    "/tmp/autosave_canvas.png").

### Starter Code

Use this skeleton for your DrawingCanvas widget:

```
// drawingcanvas.h - Starter skeleton
#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H
```
```
#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPoint>
```
```
class DrawingCanvas : public QWidget
{
Q_OBJECT
public:
explicit DrawingCanvas(QWidget *parent = nullptr);
void setPenColor(const QColor &color);
void setPenWidth(int width);
void clearCanvas();
bool saveImage(const QString &filePath);
bool loadImage(const QString &filePath);
bool isModified() const;
```
```
protected:
void paintEvent(QPaintEvent *event) override;
void mousePressEvent(QMouseEvent *event) override;
void mouseMoveEvent(QMouseEvent *event) override;
void mouseReleaseEvent(QMouseEvent *event) override;
```
```
private:
QImage canvas;
QColor penColor;
int penWidth;
bool drawing;
bool modified;
QPoint lastPoint;
};
```
```
#endif
```

# Sample output:

**(Drawing Canvas)** shows the application with the toolbar (New/Open/Save, color chooser with
red preview square, width slider at 5px, style dropdown set to Solid, auto-save checkbox
enabled, Clear button), a white canvas with sample freehand drawings in multiple colors, and
the status bar showing the auto-save path and current pen settings.