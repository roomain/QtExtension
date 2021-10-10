#pragma once
#include "qtwidgetsex_global.h"
#include <QWidget>
namespace Ui { class HorizontalSlider; };

namespace Qt::WidgetsEx
{
	class QTWIDGETSEX_EXPORT HorizontalSlider : public QWidget
	{
		Q_OBJECT

	public:
		HorizontalSlider(QWidget* parent = Q_NULLPTR);
		~HorizontalSlider();
		void setRange(const int iMin, const int iMax);

	signals:
		void sg_valueChanged(int);

	private:
		Ui::HorizontalSlider* ui;
	};
}
