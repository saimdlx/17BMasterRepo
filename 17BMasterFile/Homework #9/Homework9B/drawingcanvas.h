// ================================================================
// Programmer: Saim Ahmed
// Class: CIS17B
// Instructor: Med Mogasemi
// ================================================================
// Program: HW9B - Drawing Canvas Header File
// ================================================================
// Program Description:
// Drawing Canvas Header File
// - Defines the custom drawing surface widget.
// - Manages canvas state, drawing properties, and mouse events.
// ================================================================
#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H
#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPoint>

class DrawingCanvas : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    void setPenColor(const QColor &color);
    void setPenWidth(int width);
    void setPenStyle(Qt::PenStyle style);
    void clearCanvas();
    bool saveImage(const QString &filePath, bool resetModified = true);
    bool loadImage(const QString &filePath);
    bool isModified() const;
    void setModified(bool modified);

protected:
    // ================================================================
    // Event Handlers:
    // - paintEvent(): Redraws the canvas.
    // - mousePressEvent(): Initiates drawing.
    // - mouseMoveEvent(): Continues drawing a line.
    // - mouseReleaseEvent(): Finishes drawing a line.
    // - resizeEvent(): Handles resizing of the widget and canvas.
    // ================================================================
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);

    // ================================================================
    // Canvas Components and State:
    // - canvas: Stores the actual image data being drawn on.
    // - penColor: Current color of the drawing pen.
    // - penWidth: Current thickness of the drawing pen.
    // - penStyle: Current style of the drawing pen (solid, dash, etc.).
    // - drawing: Tracks whether the user is actively drawing.
    // - modified: Indicates if the canvas has unsaved changes.
    // - lastPoint: Stores the last recorded mouse position.
    // ================================================================
    QImage canvas;
    QColor penColor;
    int penWidth;
    Qt::PenStyle penStyle;
    bool drawing;
    bool modified;
    QPoint lastPoint;
};
#endif
