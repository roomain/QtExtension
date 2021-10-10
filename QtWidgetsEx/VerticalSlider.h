#pragma once
#include "qtwidgetsex_global.h"
#include <QWidget>
namespace Ui { class VerticalSlider; };
namespace Qt::WidgetsEx
{
	class QTWIDGETSEX_EXPORT VerticalSlider : public QWidget
	{
		Q_OBJECT

	public:
		VerticalSlider(QWidget* parent = Q_NULLPTR);
		~VerticalSlider();
		void setRange(const int iMin, const int iMax);

	signals:
		void sg_valueChanged(int);

	private:
		Ui::VerticalSlider* ui;
	};
}
