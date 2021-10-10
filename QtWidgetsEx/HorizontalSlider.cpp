#include "HorizontalSlider.h"
#include "ui_HorizontalSlider.h"

namespace Qt::WidgetsEx
{
	HorizontalSlider::HorizontalSlider(QWidget* parent)
		: QWidget(parent)
	{
		ui = new Ui::HorizontalSlider();
		ui->setupUi(this);
		QObject::connect(ui->spBx, SLOT(valueChanged(int)), this, SIGNAL(sg_valueChanged(int)));
	}

	HorizontalSlider::~HorizontalSlider()
	{
		delete ui;
	}

	void HorizontalSlider::setRange(const int iMin, const int iMax)
	{
		ui->spBx->setRange(iMin, iMax);
		ui->hSlider->setRange(iMin, iMax);
	}
}