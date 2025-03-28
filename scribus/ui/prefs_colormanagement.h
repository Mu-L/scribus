/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/

#ifndef PREFS_COLORMANAGEMENT_H
#define PREFS_COLORMANAGEMENT_H

#include "colormgmt/sccolormgmtstructs.h"
#include "ui_prefs_colormanagementbase.h"
#include "prefs_pane.h"
#include "scribusapi.h"

class ScribusDoc;

class SCRIBUS_API Prefs_ColorManagement : public Prefs_Pane, Ui::Prefs_ColorManagement
{
	Q_OBJECT

	public:
		Prefs_ColorManagement(QWidget* parent, ScribusDoc* doc = nullptr);
		~Prefs_ColorManagement() = default;

		void restoreDefaults(struct ApplicationPrefs *prefsData) override;
		void saveGuiToPrefs(struct ApplicationPrefs *prefsData) const override;

		void setProfiles(struct ApplicationPrefs *prefsData, ScProfileInfoMap *inputProfiles, ScProfileInfoMap *inputProfilesCMYK, ScProfileInfoMap *printerProfiles, ScProfileInfoMap *monitorProfiles);
		bool cmActive();

	protected:
		bool m_canChangeMonitorProfile;
		ScribusDoc *m_Doc;

	public slots:
		void languageChange();

	protected slots:
		void cmActivated(bool);
		void simulatePrinter(bool);

};

#endif // PREFS_COLORMANAGEMENT_H
