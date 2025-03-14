/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#include <QEvent>
#include <QToolTip>

#include "smlinestylewidget.h"
#include "colorcombo.h"
#include "iconmanager.h"
#include "linecombo.h"
#include "sccolorengine.h"
#include "scribusapp.h"
#include "scrspinbox.h"
#include "util_color.h"
#include "util.h"


SMLineStyleWidget::SMLineStyleWidget()
{
	setupUi(this);

	colorCombo->setPixmapType(ColorCombo::fancyPixmaps);

	addButton->setIcon(IconManager::instance().loadIcon("stroke-add"));
	removeButton->setIcon(IconManager::instance().loadIcon("stroke-remove"));

	lineWidth->setMinimum(0.0);
	lineWidth->setMaximum(300.0);

	fillEndCombo();
	fillJoinCombo();

	languageChange();

	connect(ScQApp, SIGNAL(iconSetChanged()), this, SLOT(iconSetChange()));
}

void SMLineStyleWidget::changeEvent(QEvent *e)
{
	if (e->type() == QEvent::LanguageChange)
	{
		languageChange();
	}
}

void SMLineStyleWidget::iconSetChange()
{
	IconManager& iconManager = IconManager::instance();

	addButton->setIcon(iconManager.loadIcon("stroke-add"));
	removeButton->setIcon(iconManager.loadIcon("stroke-remove"));

	int  oldEndComboIndex = endCombo->currentIndex();
	bool endComboBlocked  = endCombo->blockSignals(true);

	int  oldJoinComboIndex = joinCombo->currentIndex();
	bool joinComboBlocked  = joinCombo->blockSignals(true);

	fillEndCombo();
	fillJoinCombo();

	endCombo->setCurrentIndex(oldEndComboIndex);
	endCombo->blockSignals(endComboBlocked);

	joinCombo->setCurrentIndex(oldJoinComboIndex);
	joinCombo->blockSignals(joinComboBlocked);
}

void SMLineStyleWidget::languageChange()
{
	int  oldEndComboIndex = endCombo->currentIndex();
	bool endComboBlocked  = endCombo->blockSignals(true);

	int  oldJoinComboIndex = joinCombo->currentIndex();
	bool joinComboBlocked  = joinCombo->blockSignals(true);

	int  oldLineListRow  = lineStyles->currentRow();
	bool lineListBlocked = lineStyles->blockSignals(true);

	retranslateUi(this);
	fillEndCombo();
	fillJoinCombo();
	updateLineList();

	endCombo->setCurrentIndex(oldEndComboIndex);
	endCombo->blockSignals(endComboBlocked);

	joinCombo->setCurrentIndex(oldJoinComboIndex);
	joinCombo->blockSignals(joinComboBlocked);

	if (oldLineListRow >= 0)
		lineStyles->setCurrentRow(oldLineListRow);
	lineStyles->blockSignals(lineListBlocked);
}


void SMLineStyleWidget::unitChange(int unitIndex)
{
	lineWidth->setNewUnit(unitIndex);
}

void SMLineStyleWidget::fillEndCombo()
{
	IconManager& im  = IconManager::instance();

	endCombo->clear();
	endCombo->addItem(im.loadIcon("stroke-cap-butt"), tr( "Flat Cap" ) );
	endCombo->addItem(im.loadIcon("stroke-cap-square"), tr( "Square Cap" ) );
	endCombo->addItem(im.loadIcon("stroke-cap-round"), tr( "Round Cap" ) );
}

void SMLineStyleWidget::fillJoinCombo()
{
	IconManager& im  = IconManager::instance();

	joinCombo->clear();
	joinCombo->addItem(im.loadIcon("stroke-join-miter"), tr( "Miter Join" ) );
	joinCombo->addItem(im.loadIcon("stroke-join-bevel"), tr( "Bevel Join" ) );
	joinCombo->addItem(im.loadIcon("stroke-join-round"), tr( "Round Join" ) );
}

void SMLineStyleWidget::showStyle(const MultiLine &lineStyle, ColorList &colorList, int subLine)
{
// 	disconnect(lineStyles, SIGNAL(highlighted(int)), this, SLOT(slotEditNewLine(int)));
	disconnect(lineStyles, SIGNAL(currentRowChanged(int)), this, SLOT(slotEditNewLine(int)));
	m_currentStyle = lineStyle;
	colorCombo->setColors(colorList, false);
	m_colors = colorList;
	updateLineList();
	slotEditNewLine(subLine);
	connect(lineStyles, SIGNAL(currentRowChanged(int)), this, SLOT(slotEditNewLine(int)));
}

void SMLineStyleWidget::slotEditNewLine(int i)
{
	lineStyles->setCurrentRow(i);
// 	lineStyles->setSelected(i, true);
	//currentLine_ = i;

	// JG #5876 protect against broken line styles 
	// JG #6099 no current item selected
	if (m_currentStyle.count() <= i || (i < 0))
		return;

	double unitRatio = lineWidth->unitRatio();

	lineWidth->setValue(m_currentStyle[i].Width * unitRatio);
	setCurrentComboItem(colorCombo, m_currentStyle[i].Color);
	shadeBox->setValue(m_currentStyle[i].Shade);
	
	dashCombo->setCurrentIndex(m_currentStyle[i].Dash - 1);
	switch (static_cast<Qt::PenCapStyle>(m_currentStyle[i].LineEnd))
	{
	case Qt::FlatCap:
		endCombo->setCurrentIndex(0);
		break;
	case Qt::SquareCap:
		endCombo->setCurrentIndex(1);
		break;
	case Qt::RoundCap:
		endCombo->setCurrentIndex(2);
		break;
	default:
		endCombo->setCurrentIndex(0);
		break;
	}

	switch (static_cast<Qt::PenJoinStyle>(m_currentStyle[i].LineJoin))
	{
	case Qt::MiterJoin:
		joinCombo->setCurrentIndex(0);
		break;
	case Qt::BevelJoin:
		joinCombo->setCurrentIndex(1);
		break;
	case Qt::RoundJoin:
		joinCombo->setCurrentIndex(2);
		break;
	default:
		joinCombo->setCurrentIndex(0);
		break;
	}
}

void SMLineStyleWidget::updateLineList()
{
	QString tmp, tmp2;
	lineStyles->clear();
	QPixmap * pm2;
	double unitRatio = lineWidth->unitRatio();
	int decimals = lineWidth->decimals();
	for (MultiLine::iterator it = m_currentStyle.begin(); it != m_currentStyle.end(); ++it)
	{
		pm2 = getWidePixmap(getColor(it->Color, it->Shade));
		tmp2 = " "+ tmp.setNum(it->Width * unitRatio, 'f', decimals) + lineWidth->suffix() + " ";
		if (it->Dash < 6)
			tmp2 += CommonStrings::translatePenStyleName(static_cast<Qt::PenStyle>(it->Dash)) + " ";
		lineStyles->addItem(new QListWidgetItem(*pm2, tmp2, lineStyles));
	}
}

QColor SMLineStyleWidget::getColor(const QString &name, int shade)
{
	const ScColor& color = m_colors[name];
	QColor tmpf = ScColorEngine::getDisplayColor(color, m_colors.document(), shade);
	return tmpf;
}
