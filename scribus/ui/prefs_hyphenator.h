/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#ifndef PREFS_HYPHENATOR_H
#define PREFS_HYPHENATOR_H

#include "ui_prefs_hyphenatorbase.h"
#include "prefs_pane.h"
#include "scribusapi.h"
#include "scribusstructs.h"

class ScribusDoc;

class SCRIBUS_API Prefs_Hyphenator : public Prefs_Pane, Ui::Prefs_Hyphenator
{
	Q_OBJECT

	public:
		Prefs_Hyphenator(QWidget* parent, ScribusDoc* doc = nullptr);
		~Prefs_Hyphenator() = default;

		void restoreDefaults(struct ApplicationPrefs *prefsData) override;
		void saveGuiToPrefs(struct ApplicationPrefs *prefsData) const override;

	public slots:
		void languageChange();

	protected slots:
		void addToIgnoreList();
		void editIgnoreListEntry();
		void editIgnoreListItem(QListWidgetItem* item);
		void ignoreListItemChanged(QListWidgetItem* item);
		void removeFromIgnoreList();
		void enableIgnoreButtons();
		void addToExceptionList();
		void editExceptionListEntry();
		void editExceptionListItem(QListWidgetItem* item);
		void exceptionListItemChanged(QListWidgetItem* item);
		void removeFromExceptionList();
		void enableExceptionButtons();

	protected:
		QString affixFileName(QStringList files);
		QString dictFileName(QStringList files);
		void setAvailDictsXMLFile(QString availDictsXMLDataFile);

		QMap<QString, QString> dictionaryMap;
		QStringList dictionaryPaths;

};

#endif // PREFS_HYPHENATOR_H
