#include "VerticalSlider.h"
#include "ui_VerticalSlider.h"

namespace Qt::WidgetsEx
{
	VerticalSlider::VerticalSlider(QWidget* parent)
		: QWidget(parent)
	{
		ui = new Ui::VerticalSlider();
		ui->setupUi(this);
		QObject::connect(ui->spBx, SLOT(valueChanged(int)), this, SIGNAL(sg_valueChanged(int)));
	}

	VerticalSlider::~VerticalSlider()
	{
		delete ui;
	}

	void VerticalSlider::setRange(const int iMin, const int iMax)
	{
		ui->spBx->setRange(iMin, iMax);
		ui->vSlider->setRange(iMin, iMax);
	}
}
