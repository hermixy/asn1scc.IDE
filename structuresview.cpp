/****************************************************************************
**
** Copyright (C) 2017 N7 Mobile sp. z o. o.
** Contact: http://n7mobile.com/Space
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

#include "structuresview.h"

#include "parseddatastorage.h"
#include "asn1acnconstants.h"
#include "parsedobject.h"

using namespace Asn1Acn::Internal;

StructuresViewWidget::StructuresViewWidget() :
    OverviewWidget(new OverviewModel),
    m_modelRoot(std::shared_ptr<ParsedObject>(new ParsedObject))
{
    connect(ParsedDataStorage::instance(), &ParsedDataStorage::storageUpdated,
            this, &StructuresViewWidget::modelUpdated);

    modelUpdated();
}

StructuresViewWidget::~StructuresViewWidget()
{
    delete m_model;
}

void StructuresViewWidget::refreshModel()
{
    m_modelRoot->detachChildren();

    ParsedDataStorage *instance = ParsedDataStorage::instance();
    auto documents = instance->getAllParsedFiles();
    for (const auto &document : documents)
        m_modelRoot->addChild(document->getTreeRoot());

    m_model->setRootNode(m_modelRoot);
}

void StructuresViewWidget::modelUpdated()
{
    refreshModel();
    OverviewWidget::modelUpdated();
}

StructuresViewFactory::StructuresViewFactory()
{
    setDisplayName(tr("Structures View"));
    setPriority(500);
    setId(Constants::ASN_STRUCTURES_VIEW_ID);
}

Core::NavigationView StructuresViewFactory::createWidget()
{
    return Core::NavigationView(new StructuresViewWidget);
}