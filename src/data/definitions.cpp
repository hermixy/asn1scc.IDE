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
#include "definitions.h"

#include "visitor.h"

using namespace Asn1Acn::Internal::Data;

Definitions::Definitions(const QString &name, const SourceLocation &location)
    : Node(name, location)
{}

Definitions::~Definitions()
{
}

void Definitions::accept(Visitor &visitor) const
{
    visitor.visit(*this);
}

void Definitions::addType(std::unique_ptr<TypeAssignment> type)
{
    type->setParent(this);
    m_typeByNameMap[type->name()] = type.get();
    m_types.push_back(std::move(type));
}

void Definitions::addVariable(std::unique_ptr<VariableAssignment> variable)
{
    variable->setParent(this);
    m_variableByNameMap[variable->name()] = variable.get();
    m_variables.push_back(std::move(variable));
}

void Definitions::addImportedType(const ImportedType &type)
{
    m_importedTypes.push_back(type);
}

void Definitions::addImportedVariable(const ImportedVariable &variable)
{
    m_importedVariables.push_back(variable);
}

const TypeAssignment *Definitions::type(const QString &name) const
{
    const auto it = m_typeByNameMap.find(name);
    return it != m_typeByNameMap.end() ? it->second : nullptr;
}

const VariableAssignment *Definitions::variable(const QString &name) const
{
    const auto it = m_variableByNameMap.find(name);
    return it != m_variableByNameMap.end() ? it->second : nullptr;
}
