/*
 * itemwidget.cpp
 * Copyright 2017 - ~, Apin <apin.klas@gmail.com>
 *
 * This file is part of Turbin.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "itemwidget.h"
#include "ui_itemwidget.h"
#include "tablewidget.h"
#include "tablemodel.h"
#include "global_constant.h"
#include "guiutil.h"
#include "tableview.h"
#include "db_constant.h"
#include "tableitem.h"

using namespace LibGUI;
using namespace LibG;

ItemWidget::ItemWidget(LibG::MessageBus *bus, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemWidget),
    mMainTable(new TableWidget(this)),
    mSecondTable(new TableWidget(this))
{
    ui->setupUi(this);
    setMessageBus(bus);
    ui->splitter->setStretchFactor(0, 3);
    ui->splitter->setStretchFactor(1, 2);
    mMainTable->initCrudButton();
    auto model = mMainTable->getModel();
    model->setMessageBus(bus);
    model->addColumn("barcode", tr("Barcode"));
    model->addColumn("name", tr("Name"));
    model->addColumnMoney("buy_price", tr("Buy Price"));
    model->addColumnMoney("sell_price", tr("Sell Price"));
    model->addColumnMoney("stock", tr("Stock"));
    model->addColumn("category", tr("Category"));
    model->addColumn("suplier", tr("Suplier"));
    model->setTypeCommand(MSG_TYPE::ITEM, MSG_COMMAND::QUERY);
    mMainTable->setupTable();
    GuiUtil::setColumnWidth(mMainTable->getTableView(), QList<int>() << 150 << 150 << 150 << 150 << 150 << 150 << 150);
    mMainTable->getTableView()->horizontalHeader()->setStretchLastSection(true);
    model->refresh();
    ui->verticalLayoutTop->addWidget(mMainTable);

    mSecondTable->initCrudButton();
    model = mSecondTable->getModel();
    model->setMessageBus(bus);
    model->addColumn("barcode", tr("Barcode"));
    model->addColumn("name", tr("Name"));
    model->addColumnMoney("count", tr("Count"));
    model->addColumnMoney("price", tr("Sell Price"));
    model->setTypeCommand(MSG_TYPE::SELLPRICE, MSG_COMMAND::QUERY);
    mSecondTable->setupTable();
    GuiUtil::setColumnWidth(mSecondTable->getTableView(), QList<int>() << 150 << 150 << 150 << 150);
    mSecondTable->getTableView()->horizontalHeader()->setStretchLastSection(true);
    ui->verticalLayoutBottom->addWidget(mSecondTable);

    connect(mMainTable->getTableView(), SIGNAL(clicked(QModelIndex)), SLOT(mainTableSelectionChanges()));
}

ItemWidget::~ItemWidget()
{
    delete ui;
}

void ItemWidget::messageReceived(LibG::Message */*msg*/)
{
}

void ItemWidget::mainTableSelectionChanges()
{
    const QModelIndex &index = mMainTable->getTableView()->currentIndex();
    if(index.isValid()) {
        auto item = static_cast<TableItem*>(index.internalPointer());
        mSecondTable->getModel()->setFilter("barcode", COMPARE::EQUAL, item->data("barcode"));
        mSecondTable->getModel()->refresh();
    }
}
