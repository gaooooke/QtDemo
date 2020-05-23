#ifndef ANALOGCLOCKWINDOW_H
#define ANALOGCLOCKWINDOW_H

#include "rasterwindow.h"

class AnalogClockWindow : public RasterWindow
{
    Q_OBJECT

public:
    AnalogClockWindow();

protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;

private:
    int m_timerId;
};

#endif // ANALOGCLOCKWINDOW_H
