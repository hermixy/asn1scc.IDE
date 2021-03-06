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

#include <map>
#include <vector>
#include <memory>

#include <QString>
#include <QStringList>

#include "typeassignment.h"
#include "variableassignment.h"
#include "importedtype.h"
#include "importedvariable.h"
#include "node.h"

namespace Asn1Acn {
namespace Internal {
namespace Data {

class Definitions : public Node
{
public:
    Definitions(const QString &name, const SourceLocation &location);
    ~Definitions() override;

    void accept(Visitor &visitor) const override;

    void addType(std::unique_ptr<TypeAssignment> type);
    void addVariable(std::unique_ptr<VariableAssignment> variable);
    void addImportedType(const ImportedType &type);
    void addImportedVariable(const ImportedVariable &variable);

    using Types = std::vector<std::unique_ptr<TypeAssignment>>;
    using Variables = std::vector<std::unique_ptr<VariableAssignment>>;
    using ImportedTypes = std::vector<ImportedType>;
    using ImportedVariables = std::vector<ImportedVariable>;

    const Types &types() const { return m_types; }
    const TypeAssignment *type(const QString &name) const;
    const Variables &variables() const { return m_variables; }
    const VariableAssignment *variable(const QString &name) const;
    const ImportedTypes &importedTypes() const { return m_importedTypes; }
    const ImportedVariables &importedVariables() const { return m_importedVariables; }

    template <typename Functor>
    void forAllNodes(Functor fun) const
    {
        for (const auto &type : types())
            fun(type.get());
        for (const auto &var : variables())
            fun(var.get());
    }

private:
    Types m_types;
    Variables m_variables;
    std::map<QString, TypeAssignment*> m_typeByNameMap;
    std::map<QString, VariableAssignment*> m_variableByNameMap;
    ImportedTypes m_importedTypes;
    ImportedVariables m_importedVariables;
};

} // namespace Data
} // namespace Internal
} // namespace Asn1Acn
