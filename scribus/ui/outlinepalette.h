/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
#ifndef OUTLINEPALETTE_H
#define OUTLINEPALETTE_H

#include <QPixmap>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QLineEdit>
#include <QList>
#include <QLabel>

class QEvent;

#include "scribusapi.h"
//#include "scdockpalette.h"
#include "docks/dock_panelbase.h"

class ScribusMainWindow;
class ScribusDoc;
class PageItem;
class ScPage;

class SCRIBUS_API OutlineTreeItem : public QTreeWidgetItem
{
public:
	OutlineTreeItem(OutlineTreeItem* parent, OutlineTreeItem* after);
	OutlineTreeItem(QTreeWidget* parent, OutlineTreeItem* after);
	~OutlineTreeItem() {};

	PageItem *PageItemObject { nullptr };
	ScPage *PageObject { nullptr };
	ScribusDoc *DocObject { nullptr };
	int LayerID { -1 };
	int type { -1 }; //1=PageItem on Master Page,2=,3=PageItem,4=,5=,...
};

class SCRIBUS_API OutlineWidget : public QTreeWidget
{
	Q_OBJECT

public:
	OutlineWidget(QWidget* parent);
	~OutlineWidget() {};

	void selectItems(const QList<QTreeWidgetItem*>& items);

protected:
	void dropEvent(QDropEvent *e) override;
	void keyPressEvent(QKeyEvent *e) override;
	bool viewportEvent(QEvent *event) override;
};

class SCRIBUS_API OutlinePalette : public DockPanelBase
{
	Q_OBJECT

public:
	OutlinePalette( QWidget* parent );
	
	void setMainWindow(ScribusMainWindow *mw);
	void setDoc(ScribusDoc *);
	void unsetDoc();
	void reopenTree();
	QTreeWidgetItem* getListItem(int pageNr, PageItem *pageItem);
	void setItemIcon(QTreeWidgetItem *item, PageItem *pgItem);
	void parseSubGroup(OutlineTreeItem* object, QList<PageItem*> *subGroupList, int itemType, ScPage *a);
	void buildReopenVals();

public slots:
	void BuildTree(bool storeVals = true);
	void filterTree(const QString& keyword);
	void iconSetChange();
	void languageChange();
	void slotShowSelect(int pageNr, PageItem *pageItem);
	void toggleView(bool);
	void slotRightClick(QPoint point);
	void setActiveLayer(int layerID);
	void setLayerVisible(int layerID);
	void setLayerLocked(int layerID);
	void setLayerPrintable(int layerID);

signals:
	void selectElementByItem(PageItem *, bool);
	void editElementByItem(PageItem *);
	void selectPage(int);
	void selectMasterPage(QString);

protected slots:
	void slotRenameItem();
	void slotDoRename(QTreeWidgetItem* ite, int col);
	void slotMultiSelect();
	void slotSelect(QTreeWidgetItem* ite, int col);
	void slotDoubleClick(QTreeWidgetItem* ite, int col);
	void rebuildTree();

protected:
	void changeEvent(QEvent *e) override;

	void filterTree();
	void clearPalette();
	void createContextMenu(PageItem *currItem, double, double);

	bool selectionTriggered { false };
	ScribusDoc* currDoc { nullptr };
	ScribusMainWindow* m_MainWindow { nullptr };

	QWidget* containerWidget { nullptr };
	OutlineWidget* reportDisplay { nullptr };
	QTreeWidgetItem* freeObjects { nullptr };
	QTreeWidgetItem* rootObject { nullptr };
	QTreeWidgetItem* currentObject { nullptr };
	QLabel* filterLabel { nullptr };
	QLineEdit* filterEdit { nullptr };
	QPixmap textIcon;
	QPixmap imageIcon;
	QPixmap latexIcon;
	QPixmap tableIcon;
	QPixmap lineIcon;
	QPixmap polygonIcon;
	QPixmap arcIcon;
	QPixmap spiralIcon;
	QPixmap polylineIcon;
	QPixmap buttonIcon;
	QPixmap radiobuttonIcon;
	QPixmap textFieldIcon;
	QPixmap checkBoxIcon;
	QPixmap comboBoxIcon;
	QPixmap listBoxIcon;
	QPixmap annotTextIcon;
	QPixmap annotLinkIcon;
	QPixmap annot3DIcon;
	QPixmap groupIcon;
};

#endif // TREE_H
