
// Generated from asnLexer.g4 by ANTLR 4.7

#pragma once


#include "antlr4-runtime.h"




class  asnLexer : public antlr4::Lexer {
public:
  enum {
    PLUS_INFINITY = 1, MINUS_INFINITY = 2, GeneralizedTime = 3, UTCTime = 4, 
    MANTISSA = 5, BASE = 6, EXPONENT = 7, UnionMark = 8, IntersectionMark = 9, 
    DEFINITIONS = 10, EXPLICIT = 11, TAGS = 12, IMPLICIT = 13, AUTOMATIC = 14, 
    EXTENSIBILITY = 15, IMPLIED = 16, BEGIN = 17, END = 18, EXPORTS = 19, 
    ALL = 20, IMPORTS = 21, FROM = 22, UNIVERSAL = 23, APPLICATION = 24, 
    PRIVATE = 25, BIT = 26, STRING = 27, BOOLEAN = 28, ENUMERATED = 29, 
    INTEGER = 30, REAL = 31, CHOICE = 32, SEQUENCE = 33, OPTIONAL = 34, 
    SIZE = 35, OF = 36, OCTET = 37, MIN = 38, MAX = 39, TRUE = 40, FALSE = 41, 
    ABSENT = 42, PRESENT = 43, WITH = 44, COMPONENT = 45, COMPONENTS = 46, 
    DEFAULT = 47, NULLVAL = 48, PATTERN = 49, OBJECT = 50, IDENTIFIER = 51, 
    RELATIVE_OID = 52, NumericString = 53, PrintableString = 54, VisibleString = 55, 
    IA5String = 56, TeletexString = 57, VideotexString = 58, GraphicString = 59, 
    GeneralString = 60, UniversalString = 61, BMPString = 62, UTF8String = 63, 
    INCLUDES = 64, EXCEPT = 65, SET = 66, ASSIG_OP = 67, L_BRACKET = 68, 
    R_BRACKET = 69, L_PAREN = 70, R_PAREN = 71, COMMA = 72, EXT_MARK = 73, 
    DOUBLE_DOT = 74, LESS_THAN = 75, BitStringLiteral = 76, OctectStringLiteral = 77, 
    StringLiteral = 78, UID = 79, LID = 80, FloatingPointLiteral = 81, DOT = 82, 
    WS = 83, COMMENT = 84, COMMENT2 = 85
  };

  asnLexer(antlr4::CharStream *input);
  ~asnLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

