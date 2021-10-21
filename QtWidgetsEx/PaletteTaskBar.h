#pragma once

#include <QWidget>
namespace Ui { class PaletteTaskBar; };

class PaletteTaskBar : public QWidget
{
	Q_OBJECT

public:
	PaletteTaskBar(QWidget *parent = Q_NULLPTR);
	~PaletteTaskBar();

private:
	Ui::PaletteTaskBar *ui;
	void onScrollRangeChanged(int iMin, int iMax);
	void onScroll(int iValue);
	void onPrev();
	void onNext();
};
