#pragma once
#include "qtwidgetsex_global.h"
#include <QWidget>
namespace Ui { class PaletteTaskBar; };

namespace Qt::WidgetsEx
{
	class QTWIDGETSEX_EXPORT PaletteTaskBar : public QWidget
	{
		Q_OBJECT

	public:
		PaletteTaskBar(QWidget* parent = Q_NULLPTR);
		~PaletteTaskBar();

	private:
		Ui::PaletteTaskBar* ui;
		void onScrollRangeChanged(int iMin, int iMax);
		void onScroll(int iValue);
		void onPrev();
		void onNext();
	};
}