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

#include "asnhighlighterhelper.h"
#include "lexer/asnLexer.h"

using namespace Asn1Acn::Internal;
using TokenDescription = AsnHighlighterHelper::TokenDescription;

AsnHighlighterHelper::AsnFormat tokenToFormat(antlr4::Token *token)
{
    switch (token->getType()) {
    case asnLexer::COMMENT:
    case asnLexer::COMMENT2:
        return AsnHighlighterHelper::AsnFormat::Comment;
    case asnLexer::StringLiteral:
    case asnLexer::BitStringLiteral:
    case asnLexer::OctectStringLiteral:
    case asnLexer::FloatingPointLiteral:
        return AsnHighlighterHelper::AsnFormat::String;
    case asnLexer::BIT:
    case asnLexer::STRING:
    case asnLexer::BOOLEAN:
    case asnLexer::ENUMERATED:
    case asnLexer::INTEGER:
    case asnLexer::REAL:
    case asnLexer::CHOICE:
    case asnLexer::SEQUENCE:
    case asnLexer::IA5String:
        return AsnHighlighterHelper::AsnFormat::Keyword;
    case asnLexer::LID:
        return AsnHighlighterHelper::AsnFormat::Type;
    default:
        return AsnHighlighterHelper::AsnFormat::Cnt;
    }
}

std::vector<TokenDescription>
AsnHighlighterHelper::getTokensDescription(const std::string &codeBlock) const
{
    antlr4::ANTLRInputStream input(codeBlock);
    asnLexer lexer(&input);

    antlr4::CommonTokenStream tokens(&lexer);
    tokens.fill();

    std::vector<TokenDescription> formats;
    for (auto token : tokens.getTokens()) {
        AsnFormat tokenFormat = tokenToFormat(token);
        if (tokenFormat >= AsnFormat::Cnt)
            continue;

        TokenDescription description = {
            .format = tokenFormat,
            .position = token->getCharPositionInLine(),
            .length = token->getText().length()
        };

        formats.push_back(description);
    }

    return formats;
}
