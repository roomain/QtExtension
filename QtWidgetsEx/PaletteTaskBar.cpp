#include "PaletteTaskBar.h"
#include "ui_PaletteTaskBar.h"
#include <qscrollbar.h>
#include <QMouseEvent>

namespace Qt::WidgetsEx
{
	PaletteTaskBar::PaletteTaskBar(QWidget* parent)
		: QWidget(parent)
	{
		ui = new Ui::PaletteTaskBar();
		ui->setupUi(this);

		ui->pBtnPrev->setVisible(false);
		ui->pBtnNext->setVisible(false);
#ifdef __APPLE__
		ui->pBtnNext->setAttribute(Qt::WA_LayoutUsesWidgetRect);
		ui->pBtnPrev->setAttribute(Qt::WA_LayoutUsesWidgetRect);
#endif
		QObject::connect(ui->scrollArea->horizontalScrollBar(), &QScrollBar::rangeChanged, this, &PaletteTaskBar::onScrollRangeChanged);
		QObject::connect(ui->scrollArea->horizontalScrollBar(), &QScrollBar::valueChanged, this, &PaletteTaskBar::onScroll);


		QObject::connect(ui->pBtnPrev, &LongPressButton::sg_pressed, this, &PaletteTaskBar::onPrev);
		QObject::connect(ui->pBtnNext, &LongPressButton::sg_pressed, this, &PaletteTaskBar::onNext);

	}

	PaletteTaskBar::~PaletteTaskBar()
	{
		delete ui;
	}

	void PaletteTaskBar::onScrollRangeChanged(int iMin, int iMax)
	{
		if (iMin == iMax)
		{
			ui->pBtnPrev->setVisible(false);
			ui->pBtnNext->setVisible(false);
		}
		else
		{
			int iValue = ui->scrollArea->horizontalScrollBar()->value();
			ui->pBtnPrev->setVisible(ui->scrollArea->horizontalScrollBar()->value() > iMin);
			ui->pBtnNext->setVisible(ui->scrollArea->horizontalScrollBar()->value() < iMax);
		}
	}

	void PaletteTaskBar::onScroll(int iValue)
	{
		ui->pBtnPrev->setVisible(ui->scrollArea->horizontalScrollBar()->minimum() < iValue);
		ui->pBtnNext->setVisible(ui->scrollArea->horizontalScrollBar()->maximum() > iValue);
	}

	void PaletteTaskBar::onPrev()
	{
		ui->scrollArea->horizontalScrollBar()->setValue(ui->scrollArea->horizontalScrollBar()->value() - 1);
	}

	void PaletteTaskBar::onNext()
	{
		ui->scrollArea->horizontalScrollBar()->setValue(ui->scrollArea->horizontalScrollBar()->value() + 1);
	}
}