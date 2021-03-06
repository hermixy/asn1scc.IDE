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
#pragma once

#include <QString>
#include <QTextCursor>

#include <texteditor/texteditor.h>

#include "data/file.h"
#include "data/typereference.h"
#include "data/sourcelocation.h"

#include "parseddatastorage.h"

namespace Asn1Acn {
namespace Internal {

class LinkCreator
{
public:

    using Link = TextEditor::TextEditorWidget::Link;

    LinkCreator(const TextEditor::TextDocument &document, const ParsedDataStorage *storage);

    Link createHighlightLink(const QTextCursor &cursor) const;
    Link createTargetLink(const QTextCursor &cursor) const;

private:
    Link getSymbolLink(const Data::TypeReference &symbolSource, const QTextCursor &cursor) const;

    Link getTargetSymbolLink(const Data::TypeReference &symbolSource, const Link &symbol) const;

    Data::SourceLocation getTargetLocation(const QString &typeName, const QString &moduleName) const;
    Data::SourceLocation getTargetLocationFromProject(const QString &projectName,
                                                      const QString &typeName,
                                                      const QString &moduleName) const;

    const QString m_documentPath;
    const TextEditor::TextDocument &m_textDocument;
    const ParsedDataStorage *m_storage;
};

} /* namespace Internal */
} /* namespace Asn1Acn */
