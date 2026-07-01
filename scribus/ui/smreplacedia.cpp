/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#include "smreplacedia.h"

#include <QLabel>
#include <QComboBox>

SMRowWidget::SMRowWidget(StyleItem *styleType, const QString &toBeDeleted, const QStringList& replaceOptions, QWidget *parent)
: QWidget(parent),
  m_styleType(styleType)
{
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(6);
	deleteLabel = new QLabel(toBeDeleted, this);
	layout->addWidget(deleteLabel);
	optionsCombo = new QComboBox(this);
	optionsCombo->addItem( tr("No Style"));
	optionsCombo->addItems(replaceOptions);
	layout->addWidget(optionsCombo);
}

StyleItem* SMRowWidget::styleType() const
{
	return m_styleType;
}

QString SMRowWidget::toBeDeleted() const
{
	return deleteLabel->text();
}

QString SMRowWidget::replaceWith() const
{
	return optionsCombo->currentIndex() == 0 ? "" : optionsCombo->currentText();
}

SMRowWidget::~SMRowWidget()
{
	delete deleteLabel;
	delete optionsCombo;
	delete layout;
}

/*************************************************************************/
/*************************************************************************/

SMReplaceDia::SMReplaceDia(const QMap<StyleItem*, QStringList> &toBeDeleted, const QMap<StyleItem*, QStringList> &replaceOptions, QWidget *parent) : QDialog(parent)
{
	setupUi(this);

	layout = new QVBoxLayout(mainFrame);
	layout->setContentsMargins(0, 0, 0, 0);
	layout->setSpacing(6);
	headerLayout = new QHBoxLayout();
	headerLayout->setContentsMargins(0, 0, 0, 0);
	deleteHeader = new QLabel("<b>" + tr("Remove") + "</b>", mainFrame);
	optionsHeader = new QLabel("<b>" + tr("Replace with") + "</b>", mainFrame);
	headerLayout->addWidget(deleteHeader);
	headerLayout->addWidget(optionsHeader);
	layout->addLayout(headerLayout);

	// One block of rows per style type so each combo only offers replacements of
	// the matching type. A type heading is shown when more than one type is present.
	bool showTypeHeaders = toBeDeleted.count() > 1;
	QMap<StyleItem*, QStringList>::const_iterator it;
	for (it = toBeDeleted.constBegin(); it != toBeDeleted.constEnd(); ++it)
	{
		StyleItem *styleType = it.key();
		const QStringList &names = it.value();

		QStringList options = replaceOptions.value(styleType);
		options.sort(Qt::CaseSensitive);

		if (showTypeHeaders && styleType)
		{
			QLabel *typeHeader = new QLabel("<b>" + styleType->typeName() + "</b>", mainFrame);
			layout->addWidget(typeHeader);
			typeHeaders.append(typeHeader);
		}

		for (int i = 0; i < names.count(); ++i)
		{
			SMRowWidget *tmp = new SMRowWidget(styleType, names[i], options, mainFrame);
			layout->addWidget(tmp);
			rowWidgets.append(tmp);
		}
	}
	layout->addStretch(10);
}

QMap<StyleItem*, QList<RemoveItem> > SMReplaceDia::items() const
{
	QMap<StyleItem*, QList<RemoveItem> > result;
	for (int i = 0; i < rowWidgets.count(); ++i)
	{
		SMRowWidget *row = rowWidgets.at(i);
		result[row->styleType()].append(RemoveItem(row->toBeDeleted(), row->replaceWith()));
	}
	return result;
}

SMReplaceDia::~SMReplaceDia()
{
	while (!rowWidgets.isEmpty())
		delete rowWidgets.takeFirst();
	while (!typeHeaders.isEmpty())
		delete typeHeaders.takeFirst();
	delete optionsHeader;
	delete deleteHeader;
	delete headerLayout;
	delete layout;
}
