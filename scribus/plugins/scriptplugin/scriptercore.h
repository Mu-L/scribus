/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef SCRIPTERCORE_H
#define SCRIPTERCORE_H

#include "cmdvar.h"

#include "qmap.h"
#include "qpointer.h"
#include "scriptpaths.h"

class ScrAction;
class ScribusMainWindow;
class MenuManager;
class PythonConsole;

class ScripterCore : public QObject
{
	Q_OBJECT

public:
	ScripterCore(QWidget* parent);
	~ScripterCore();

	void addToMainWindowMenu(ScribusMainWindow *);
	void enableMainWindowMenu();
	void disableMainWindowMenu();

	/** @brief String representation of result returned by last python console command */
	QString returnString;
	/** @brief String representation of line of code to be passed to the Python interactive interpreter */
	QString inValue;

	ScriptPaths scriptPaths;

public slots:
	void runScriptDialog();
	void StdScript(const QString& baseFilename);
	void RecentScript(const QString& fn);
	void runScriptFile(const QString& path);
	void slotRunScriptFile(const QString& fileName, bool inMainInterpreter = false);
	void slotRunScriptFile(const QString& fileName, QStringList arguments, bool inMainInterpreter = false);
	void slotRunPythonScript(); // needed for running python script from CLI
	void slotRunScript(const QString& script);
	void slotInteractiveScript(bool);
	void slotExecute();
	/*! \brief Show docstring of the script to the user.
	* I don't know how to get docstring via e.g. pydoc because of
	* it needs to run script => error cannot find scribus module
	*/
	void aboutScript();
	/** \brief Does setup for the main interpreter, particularly the interactive console. True for success. */
	bool setupMainInterpreter();
	/** \brief Sets up the plugin for extension scripts, if enabled */
	void initExtensionScripts();
	/** \brief Runs the startup script, if enabled */
	void runStartupScript();
	void languageChange();

	// Preferences
	const QString & startupScript() const;
	bool extensionsEnabled() const;
	void setStartupScript(const QString& newScript);
	void setExtensionsEnabled(bool enable);
	void updateSyntaxHighlighter();

protected:
	// Private helper functions
	void finishScriptRun();
	void readPlugPrefs();
	void savePlugPrefs();
	void rebuildRecentScriptsMenu();
	void buildScribusScriptsMenu();
	//void buildRecentScriptsMenu();
	void rebuildScribusScriptsMenu();

	//Internal members
	//! \brief Reference to the "IDE" widget
	PythonConsole *m_pyConsole {nullptr};
	MenuManager *m_menuMgr {nullptr};
	QStringList m_savedRecentScripts;
	QStringList m_recentScripts;
	QMap<QString, QPointer<ScrAction> > m_scripterActions;
	QMap<QString, QPointer<ScrAction> > m_recentScriptActions;

	// Preferences
	/** \brief pref: Enable access to main interpreter and 'extension scripts' */
	bool m_enableExtPython {false};
	/** \brief pref: Run 'from scribus import *' at scripter startup */
	bool m_importAllNames {true};
	/** \brief pref: Load this script on startup */
	QString m_startupScript;
};

#endif
