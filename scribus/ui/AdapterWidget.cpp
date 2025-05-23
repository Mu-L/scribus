/*
For general Scribus (>=1.3.2) copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Scribus 1.3.2
for which a new license (GPL+exception) is in place.
*/
/***************************************************************************
*                                                                         *
*   This program is free software; you can redistribute it and/or modify  *
*   it under the terms of the GNU General Public License as published by  *
*   the Free Software Foundation; either version 2 of the License, or     *
*   (at your option) any later version.                                   *
*                                                                         *
***************************************************************************/
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>

#include "scconfig.h"

#include <QtCore>
#include <QtGui>
#include <QtOpenGL>
#include <iostream>
#include <iomanip>
#include <fstream>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <cstdlib>
#include <cassert>
#include <string>
#include "iconmanager.h"
#include "AdapterWidget.h"

AdapterWidget::AdapterWidget ( QWidget * parent, const char * name) : QOpenGLWidget ( parent )
{
	_gw = new osgViewer::GraphicsWindowEmbedded ( 0,0,width(),height() );
	setFocusPolicy ( Qt::ClickFocus );
	button = 0;
}

void AdapterWidget::resizeGL ( int width, int height )
{
	_gw->getEventQueue()->windowResize ( 0, 0, width, height );
	_gw->resized ( 0,0,width,height );
}

void AdapterWidget::keyPressEvent ( QKeyEvent* event )
{
	_gw->getEventQueue()->keyPress ( ( osgGA::GUIEventAdapter::KeySymbol ) * ( event->text().toLatin1().data() ) );
}

void AdapterWidget::keyReleaseEvent ( QKeyEvent* event )
{
	_gw->getEventQueue()->keyRelease ( ( osgGA::GUIEventAdapter::KeySymbol ) * ( event->text().toLatin1().data() ) );
}

void AdapterWidget::mousePressEvent ( QMouseEvent* event )
{
	switch ( event->button() )
	{
		case Qt::LeftButton:
			qApp->setOverrideCursor(QCursor(Qt::OpenHandCursor));
			button = 1;
			break;
		case Qt::MiddleButton:
			qApp->setOverrideCursor(QCursor(Qt::SizeAllCursor));
			button = 2;
			break;
		case Qt::RightButton:
			qApp->setOverrideCursor(IconManager::instance().loadCursor("cursor-zoom-in"));
			button = 3;
			break;
		case Qt::NoButton:
			qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));
			button = 0;
			break;
		default:
			qApp->setOverrideCursor(QCursor(Qt::ArrowCursor));
			button = 0;
			break;
	}
	QPoint eventPos = event->position().toPoint();
	_gw->getEventQueue()->mouseButtonPress ( eventPos.x(), eventPos.y(), button );
}

void AdapterWidget::mouseReleaseEvent ( QMouseEvent* event )
{
	switch ( event->button() )
	{
		case ( Qt::LeftButton ) : button = 1; break;
		case ( Qt::MiddleButton ) : button = 2; break;
		case ( Qt::RightButton ) : button = 3; break;
		case ( Qt::NoButton ) : button = 0; break;
		default: button = 0; break;
	}
	qApp->restoreOverrideCursor();
	QPoint eventPos = event->position().toPoint();
	_gw->getEventQueue()->mouseButtonRelease ( eventPos.x(), eventPos.y(), button );
}

void AdapterWidget::mouseMoveEvent ( QMouseEvent* event )
{
	QPoint eventPos = event->position().toPoint();
	_gw->getEventQueue()->mouseMotion ( eventPos.x(), eventPos.y() );
	emit mouseMoved();
}
