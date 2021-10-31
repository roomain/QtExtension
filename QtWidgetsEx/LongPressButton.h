#pragma once
#include <qpushbutton.h>

class LongPressButton : public QPushButton
{
	Q_OBJECT
public:
	using QPushButton::QPushButton;

signals:
	void sg_pressed();

protected:
	void mousePressEvent(QMouseEvent* evt) final;
	void mouseReleaseEvent(QMouseEvent* evt) final;
	void timerEvent(QTimerEvent* evnt)final;

private:
	int m_timerId = -1;
};

