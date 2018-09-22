/*
  problemclientmodel.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2016-2018 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "problemclientmodel.h"

#include <common/problem.h>
#include <common/objectmodel.h>
#include <common/tools/problemreporter/problemmodelroles.h>

#include <uiresources.h>

#include <QApplication>
#include <QStyle>

using namespace GammaRay;

ProblemClientModel::ProblemClientModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
}

ProblemClientModel::~ProblemClientModel()
{
}

QVariant ProblemClientModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DecorationRole) {
        auto severity = QSortFilterProxyModel::data(index, ProblemModelRoles::SeverityRole).value<int>();
        switch (severity) {
        case Problem::Info:
            return QVariant::fromValue(QIcon::fromTheme(QStringLiteral("dialog-information")));
        case Problem::Warning:
            return QVariant::fromValue(UIResources::themedIcon(QStringLiteral("warning.png")).pixmap(16, 16));
        case Problem::Error:
            return QVariant::fromValue(QIcon::fromTheme(QStringLiteral("dialog-error")));
        }
    }
    return QSortFilterProxyModel::data(index, role);
}

QVariant ProblemClientModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal) {
        if (role == Qt::DisplayRole) {
            switch (section) {
                case 0:
                    return tr("Problem Description");
                case 1:
                    return tr("Meta Type Id");
                case 2:
                    return tr("Size");
                case 3:
                    return tr("Meta Object");
                case 4:
                    return tr("Type Flags");
                case 5:
                    return tr("Compare");
                case 6:
                    return tr("Debug");
            }
        } else if (role == Qt::ToolTipRole) {
            switch (section) {
                case 5:
                    return tr("Has equality comparison operators registered.");
                case 6:
                    return tr("Has debug stream operators registered.");
            }
        }
        return QVariant();
    }
    return QSortFilterProxyModel::headerData(section, orientation, role);
}
