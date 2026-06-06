// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW9B - Drawing Canvas Implementation Class File
// ================================================================
// Program Description:
// Implementation of the Drawing Canvas class.
// - Handles mouse events for drawing on an image canvas.
// - Manages resizing events and updating the display.
// - Provides functions for pen settings and saving/loading images.
// ================================================================
#include "drawingcanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>

DrawingCanvas::DrawingCanvas(QWidget *parent) : QWidget(parent), penColor(Qt::black), penWidth(2), penStyle(Qt::SolidLine), drawing(false), modified(false) {}

// ================================================================
// Function: setPenColor
// - Updates the current pen color used for drawing.
// ================================================================
void DrawingCanvas::setPenColor(const QColor &color) {
    penColor = color;
}

// ================================================================
// Function: setPenWidth
// - Updates the current pen width used for drawing.
// ================================================================
void DrawingCanvas::setPenWidth(int width) {
    penWidth = width;
}

// ================================================================
// Function: setPenStyle
// - Updates the current pen style.
// ================================================================
void DrawingCanvas::setPenStyle(Qt::PenStyle style) {
    penStyle = style;
}

// ================================================================
// Function: clearCanvas
// - Fills the entire canvas with white pixels.
// - Flags the canvas as modified and requests an update.
// ================================================================
void DrawingCanvas::clearCanvas() {
    canvas.fill(qRgb(255, 255, 255));
    modified = true;
    update();
}

// ================================================================
// Function: saveImage
// - Saves the current canvas image to the specified file path.
// - Resets the modified flag upon successful save.
// ================================================================
bool DrawingCanvas::saveImage(const QString &filePath, bool resetModified) {
    if (canvas.save(filePath)) {
        if (resetModified)
            modified = false;
        return true;
    }
    return false;
}

// ================================================================
// Function: loadImage
// - Loads an image from the specified file path into the canvas.
// - Resets the modified flag and requests an update upon success.
// ================================================================
bool DrawingCanvas::loadImage(const QString &filePath) {
    QImage loadedImage;
    if (!loadedImage.load(filePath))
        return false;

    canvas = loadedImage;
    modified = false;
    update();
    return true;
}

// ================================================================
// Function: isModified
// - Returns true if the canvas has unsaved changes.
// ================================================================
bool DrawingCanvas::isModified() const {
    return modified;
}

// ================================================================
// Function: setModified
// - Manually sets the modified state of the canvas.
// ================================================================
void DrawingCanvas::setModified(bool m)
{
    modified = m;
}

// ================================================================
// Function: resizeEvent
// - Triggered when the widget is resized.
// - Expands the internal QImage to accommodate the new size while
//   preserving existing drawing content.
// ================================================================
void DrawingCanvas::resizeEvent(QResizeEvent *event) {
    if (width() > canvas.width() || height() > canvas.height()) {
        int newWidth = qMax(width() + 128, canvas.width());
        int newHeight = qMax(height() + 128, canvas.height());
        QImage newCanvas(newWidth, newHeight, QImage::Format_RGB32);
        newCanvas.fill(qRgb(255, 255, 255));
        QPainter painter(&newCanvas);
        painter.drawImage(QPoint(0, 0), canvas);
        canvas = newCanvas;
    }
    QWidget::resizeEvent(event);
}

// ================================================================
// Function: paintEvent
// - Triggered when the widget needs to be repainted.
// - Draws the relevant portion of the QImage onto the widget.
// ================================================================
void DrawingCanvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, canvas, dirtyRect);
}

// ================================================================
// Function: mousepressEvent
// - Triggered when a mouse button is pressed.
// - Begins a drawing operation if the left button is pressed.
// ================================================================
void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

// ================================================================
// Function: mouseMoveEvent
// - Triggered when the mouse moves within the widget.
// - Continues the drawing line if the left button is held down.
// ================================================================
void DrawingCanvas::mouseMoveEvent(QMouseEvent *event) {
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        drawLineTo(event->pos());
    }
}

// ================================================================
// Function: mouseReleaseEvent
// - Triggered when a mouse button is released.
// - Completes the current drawing operation.
// ================================================================
void DrawingCanvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && drawing) {
        drawLineTo(event->pos());
        drawing = false;
    }
}

// ================================================================
// Function: drawLineTo
// - Draws a line segment from the last point to the new end point
// - Updates the modified flag and triggers a repaint for the affected area
// ================================================================
void DrawingCanvas::drawLineTo(const QPoint &endPoint) {
    QPainter painter(&canvas);
    painter.setPen(QPen(penColor, penWidth, penStyle, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (penWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized().adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;
}
