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
#include "librarieswidget.h"

#include <QFileDialog>

#include <libraries/metadata/general.h>

using namespace Asn1Acn::Internal::OptionsPages;
using namespace Asn1Acn::Internal;

namespace {

enum class Columns {
    Name,
    Version,
    Path,
};

class LibEntryItem : public QTreeWidgetItem
{
  public:
    LibEntryItem(QTreeWidgetItem *parent, const QString &path)
        : QTreeWidgetItem(parent, QTreeWidgetItem::UserType + 1)
        , m_info(QFileInfo(path).baseName(), path)
    {
    }

    QString libPath() const { return m_info.path(); }

    QVariant data(int column, int role) const override
    {
        if (role == Qt::ForegroundRole && !isValid())
            return QColor(Qt::red);
        if (role != Qt::DisplayRole)
            return QTreeWidgetItem::data(column, role);
        switch (static_cast<Columns>(column)) {
        case Columns::Name:
            return m_info.name();
        case Columns::Version:
            return m_info.version();
        case Columns::Path:
            return m_info.path();
        }
        return {};
    }

private:
    bool isValid() const { return QDir(libPath()).exists(); }

    Libraries::Metadata::General m_info;
};
} // namespace

LibrariesWidget::LibrariesWidget(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);

    m_ui.treeWidget->setUniformRowHeights(true);
    m_ui.treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_ui.treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    QHeaderView *header = m_ui.treeWidget->header();
    header->setStretchLastSection(false);
    header->setSectionResizeMode(static_cast<int>(Columns::Name), QHeaderView::ResizeToContents);
    header->setSectionResizeMode(static_cast<int>(Columns::Version), QHeaderView::ResizeToContents);
    header->setSectionResizeMode(static_cast<int>(Columns::Path), QHeaderView::Stretch);

    m_detectedRootItem = new QTreeWidgetItem(m_ui.treeWidget);
    m_detectedRootItem->setText(0, tr("Auto-detected"));
    m_manualRootItem = new QTreeWidgetItem(m_ui.treeWidget);
    m_manualRootItem->setText(0, tr("Manual"));

    connect(m_ui.treeWidget, &QTreeWidget::itemClicked, [this](QTreeWidgetItem* item, int) {
        m_ui.removeButton->setEnabled(isManualItem(item));
    });

    connect(m_ui.removeButton, &QPushButton::clicked, [this](){
       for (const auto &item : m_ui.treeWidget->selectedItems())
           delete item;
    });

    connect(m_ui.addButton, &QPushButton::clicked, [this]() {
       const auto dir = QFileDialog::getExistingDirectory(this, tr("Select ASN.1/ACN components library directory"));
       if (dir.isEmpty())
           return;
       new LibEntryItem(m_manualRootItem, dir);
    });

    m_ui.treeWidget->expandAll();
}

LibrariesWidget::~LibrariesWidget()
{
}

namespace {
void replaceAllChildren(QTreeWidgetItem *item, const QStringList &texts)
{
    while (item->childCount() > 0)
        delete item->child(0);
    for (const auto &text : texts)
        new LibEntryItem(item, text);
}
}

void LibrariesWidget::setDetectedLibPaths(const QStringList &paths)
{
    replaceAllChildren(m_detectedRootItem, paths);
}

void LibrariesWidget::setManualLibPaths(const QStringList &paths)
{
    replaceAllChildren(m_manualRootItem, paths);
}

QStringList LibrariesWidget::manualLibPaths() const
{
    QStringList res;
    for (int i = 0; i < m_manualRootItem->childCount(); ++i)
        res << static_cast<LibEntryItem *>(m_manualRootItem->child(i))->libPath();
    return res;
}

bool LibrariesWidget::isManualItem(QTreeWidgetItem *item) const
{
    return item->parent() == m_manualRootItem;
}
