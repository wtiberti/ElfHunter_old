/*
* This file is part of ElfHunter software.
*
* ElfHunter is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* ElfHunter is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with ElfHunter.  If not, see <http://www.gnu.org/licenses/>.
*
* Copyright (C) 2012 Walter Tiberti
*/

/*
* Filename: ElfHunterSideWidget.cpp
* Author: Walter Tiberti <wtuniv@gmail.com>
*
*/

#include "ElfHunterSideWidget.h"

ElfHunterSideWidget::ElfHunterSideWidget( QWidget *parent ) : QWidget(parent)
{
	layout = new QVBoxLayout();
	ss.clear();
	current_widget = 0;
	
	setLayout( layout );
}

ElfHunterSideWidget::~ElfHunterSideWidget()
{
	clearwidgets();
	delete layout;
}

void ElfHunterSideWidget::addTab( QWidget *w, QString title )
{
	w->hide();
	layout->addWidget( w );
	
	ss << title;
	elems.push_back( w );
}

void ElfHunterSideWidget::clearwidgets()
{
	for( unsigned int i=0; i<elems.size(); i++ )
		delete elems[i];
	
	ss.clear();
	elems.clear();
}

void ElfHunterSideWidget::setwidget( QTreeWidgetItem *item, int col )
{
	int temp_item_index;
	
	temp_item_index = GetTreeItemIndex(item);
	
	if( temp_item_index!=-1 && temp_item_index < (int)elems.size() )
	{
		//???->setBackground( QBrush(Qt::transparent) );
		elems[current_widget]->hide();
		//TODO COLORING BACKGROUND
		//item->setBackground( 0, QBrush(Qt::cyan) );
		elems[temp_item_index]->show();
		
		current_widget = temp_item_index;
	}
}

int ElfHunterSideWidget::GetTreeItemIndex( QTreeWidgetItem *item )
{
	//TODO a better way to find the index
	for( int i=0; i<ss.size(); i++ )
	{
		if( item->text(0) == ss[i] )
			return i;
	}
	return -1;
}