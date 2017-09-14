/****************************************************************************
**
** Copyright (C) 2017 N7 Mobile sp. z o. o.
** Contact: http://n7mobile.pl/Space
**
** This file is part of ASN.1/ACN Plugin for QtCreator.
**
** Plugin was developed under a programme and funded by
** European Space Agency.
**
** This Plugin is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This Plugin is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/

#include <QModelIndex>

#include "modeltreenode.h"

#include "coreplugin/editormanager/editormanager.h"

namespace Asn1Acn {
namespace Internal {

class OverviewActivateHandler
{
public:
    static void gotoSymbol(const QModelIndex &index)
    {
        if (!index.isValid())
            return;

        ModelTreeNode *node = static_cast<ModelTreeNode *>(index.internalPointer());

        const auto location = node->sourceLocation();
        Core::EditorManager::openEditorAt(location.path(),
                                          location.line(),
                                          location.column());
    }
};

} /* namespace Internal */
} /* namespace Asn1Acn */