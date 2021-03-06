/*
 * util.cpp
 * Copyright 2017 - ~, Apin <apin.klas@gmail.com>
 *
 * This file is part of Sultan.
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
#include "util.h"

using namespace LibG;

Util::Util()
{

}

QDate Util::getBeginningOfMonth()
{
    auto now = QDate::currentDate();
    QDate retVal;
    retVal.setDate(now.year(), now.month(), 1);
    return retVal;
}

QDate Util::getEndOfMonth()
{
    auto retVal = getBeginningOfMonth();
    retVal = retVal.addMonths(1);
    retVal = retVal.addDays(-1);
    return retVal;
}

int Util::getIntVersion(QString version)
{
    version = version.replace(".", "");
    return version.toInt();
}
