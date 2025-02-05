/* -*- Mode: C++; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 * vim: set ts=8 sts=4 et sw=4 tw=99:
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef frontend_TokenKind_h
#define frontend_TokenKind_h

/*
 * List of token kinds and their ranges.
 *
 * The format for each line is:
 *
 *   macro(<TOKEN_KIND_NAME>, <DESCRIPTION>)
 *
 * or
 *
 *   range(<TOKEN_RANGE_NAME>, <TOKEN_KIND_NAME>)
 *
 * where ;
 * <TOKEN_KIND_NAME> is a legal C identifier of the token, that will be used in
 * the JS engine source, with `TOK_` prefix.
 *
 * <DESCRIPTION> is a string that describe about the token, and will be used in
 * error message.
 *
 * <TOKEN_RANGE_NAME> is a legal C identifier of the range that will be used to
 * JS engine source, with `TOK_` prefix. It should end with `_FIRST` or `_LAST`.
 * This is used to check TokenKind by range-testing:
 *   TOK_BINOP_FIRST <= tt && tt <= TOK_BINOP_LAST
 *
 * Second argument of `range` is the actual value of the <TOKEN_RANGE_NAME>,
 * should be same as one of <TOKEN_KIND_NAME> in other `macro`s.
 *
 * To use this macro, define two macros for `macro` and `range`, and pass them
 * as arguments.
 *
 *   #define EMIT_TOKEN(name, desc) ...
 *   #define EMIT_RANGE(name, value) ...
 *   FOR_EACH_TOKEN_KIND_WITH_RANGE(EMIT_TOKEN, EMIT_RANGE)
 *   #undef EMIT_TOKEN
 *   #undef EMIT_RANGE
 *
 * If you don't need range data, use FOR_EACH_TOKEN_KIND instead.
 *
 *   #define EMIT_TOKEN(name, desc) ...
 *   FOR_EACH_TOKEN_KIND(EMIT_TOKEN)
 *   #undef EMIT_TOKEN
 *
 * Note that this list does not contain ERROR and LIMIT.
 */
#define FOR_EACH_TOKEN_KIND_WITH_RANGE(macro, range) \
    macro(EOF,         "end of script") \
    \
    /* only returned by peekTokenSameLine() */ \
    macro(EOL,          "line terminator") \
    \
    macro(SEMI,         "';'") \
    macro(COMMA,        "','") \
    macro(HOOK,         "'?'")    /* conditional */ \
    macro(COLON,        "':'")    /* conditional */ \
    macro(INC,          "'++'")   /* increment */ \
    macro(DEC,          "'--'")   /* decrement */ \
    macro(DOT,          "'.'")    /* member operator */ \
    macro(TRIPLEDOT,    "'...'")  /* rest arguments and spread operator */ \
    macro(OPTCHAIN,     "'?.'") \
    macro(LB,           "'['") \
    macro(RB,           "']'") \
    macro(LC,           "'{'") \
    macro(RC,           "'}'") \
    macro(LP,           "'('") \
    macro(RP,           "')'") \
    macro(NAME,         "identifier") \
    macro(NUMBER,       "numeric literal") \
    macro(STRING,       "string literal") \
    \
    /* start of template literal with substitutions */ \
    macro(TEMPLATE_HEAD,    "'${'") \
    /* template literal without substitutions */ \
    macro(NO_SUBS_TEMPLATE, "template literal") \
    \
    macro(REGEXP,       "regular expression literal") \
    macro(TRUE,         "boolean literal 'true'") \
    range(RESERVED_WORD_LITERAL_FIRST, TRUE) \
    macro(FALSE,        "boolean literal 'false'") \
    macro(NULL,         "null literal") \
    range(RESERVED_WORD_LITERAL_LAST, NULL) \
    macro(THIS,         "keyword 'this'") \
    range(KEYWORD_FIRST, THIS) \
    macro(FUNCTION,     "keyword 'function'") \
    macro(IF,           "keyword 'if'") \
    macro(ELSE,         "keyword 'else'") \
    macro(SWITCH,       "keyword 'switch'") \
    macro(CASE,         "keyword 'case'") \
    macro(DEFAULT,      "keyword 'default'") \
    macro(WHILE,        "keyword 'while'") \
    macro(DO,           "keyword 'do'") \
    macro(FOR,          "keyword 'for'") \
    macro(BREAK,        "keyword 'break'") \
    macro(CONTINUE,     "keyword 'continue'") \
    macro(VAR,          "keyword 'var'") \
    macro(CONST,        "keyword 'const'") \
    macro(WITH,         "keyword 'with'") \
    macro(RETURN,       "keyword 'return'") \
    macro(NEW,          "keyword 'new'") \
    macro(DELETE,       "keyword 'delete'") \
    macro(TRY,          "keyword 'try'") \
    macro(CATCH,        "keyword 'catch'") \
    macro(FINALLY,      "keyword 'finally'") \
    macro(THROW,        "keyword 'throw'") \
    macro(DEBUGGER,     "keyword 'debugger'") \
    macro(EXPORT,       "keyword 'export'") \
    macro(IMPORT,       "keyword 'import'") \
    macro(CLASS,        "keyword 'class'") \
    macro(EXTENDS,      "keyword 'extends'") \
    macro(SUPER,        "keyword 'super'") \
    range(KEYWORD_LAST, SUPER) \
    \
    /* contextual keywords */ \
    macro(AS,           "'as'") \
    range(CONTEXTUAL_KEYWORD_FIRST, AS) \
    macro(ASYNC,        "'async'") \
    macro(AWAIT,        "'await'") \
    macro(EACH,         "'each'") \
    macro(FROM,         "'from'") \
    macro(GET,          "'get'") \
    macro(LET,          "'let'") \
    macro(OF,           "'of'") \
    macro(SET,          "'set'") \
    macro(STATIC,       "'static'") \
    macro(TARGET,       "'target'") \
    macro(YIELD,        "'yield'") \
    range(CONTEXTUAL_KEYWORD_LAST, YIELD) \
    \
    /* future reserved words */ \
    macro(ENUM,         "reserved word 'enum'") \
    range(FUTURE_RESERVED_KEYWORD_FIRST, ENUM) \
    range(FUTURE_RESERVED_KEYWORD_LAST, ENUM) \
    \
    /* reserved words in strict mode */ \
    macro(IMPLEMENTS,   "reserved word 'implements'") \
    range(STRICT_RESERVED_KEYWORD_FIRST, IMPLEMENTS) \
    macro(INTERFACE,    "reserved word 'interface'") \
    macro(PACKAGE,      "reserved word 'package'") \
    macro(PRIVATE,      "reserved word 'private'") \
    macro(PROTECTED,    "reserved word 'protected'") \
    macro(PUBLIC,       "reserved word 'public'") \
    range(STRICT_RESERVED_KEYWORD_LAST, PUBLIC) \
    \
    /* \
     * The following token types occupy contiguous ranges to enable easy \
     * range-testing. \
     */ \
    /* \
     * Binary operators tokens. \
     * These must be in the same order in several places: \
     *   - the precedence table and JSOp code list in Parser.cpp \
     *   - the binary operators in ParseNode.h \
     *   - the first and last binary operator markers in ParseNode.h \
     */ \
    macro(COALESCE,     "'\?\?'") /* escapes to avoid trigraphs warning */ \
    range(BINOP_FIRST,  COALESCE) \
    macro(OR,           "'||'")   /* logical or */ \
    macro(AND,          "'&&'")   /* logical and */ \
    macro(BITOR,        "'|'")    /* bitwise-or */ \
    macro(BITXOR,       "'^'")    /* bitwise-xor */ \
    macro(BITAND,       "'&'")    /* bitwise-and */ \
    \
    /* Equality operation tokens, per TokenKindIsEquality. */ \
    macro(STRICTEQ,     "'==='") \
    range(EQUALITY_START, STRICTEQ) \
    macro(EQ,           "'=='") \
    macro(STRICTNE,     "'!=='") \
    macro(NE,           "'!='") \
    range(EQUALITY_LAST, NE) \
    \
    /* Relational ops, per TokenKindIsRelational. */ \
    macro(LT,           "'<'") \
    range(RELOP_START, LT) \
    macro(LE,           "'<='") \
    macro(GT,           "'>'") \
    macro(GE,           "'>='") \
    range(RELOP_LAST, GE) \
    \
    macro(INSTANCEOF,   "keyword 'instanceof'") \
    range(KEYWORD_BINOP_FIRST, INSTANCEOF) \
    macro(IN,           "keyword 'in'") \
    range(KEYWORD_BINOP_LAST, IN) \
    \
    /* Shift ops, per TokenKindIsShift. */ \
    macro(LSH,          "'<<'") \
    range(SHIFTOP_START, LSH) \
    macro(RSH,          "'>>'") \
    macro(URSH,         "'>>>'") \
    range(SHIFTOP_LAST, URSH) \
    \
    macro(ADD,          "'+'") \
    macro(SUB,          "'-'") \
    macro(MUL,          "'*'") \
    macro(DIV,          "'/'") \
    macro(MOD,          "'%'") \
    macro(POW,          "'**'") \
    range(BINOP_LAST,   POW) \
    \
    /* Unary operation tokens. */ \
    macro(TYPEOF,       "keyword 'typeof'") \
    range(KEYWORD_UNOP_FIRST, TYPEOF) \
    macro(VOID,         "keyword 'void'") \
    range(KEYWORD_UNOP_LAST, VOID) \
    macro(NOT,          "'!'") \
    macro(BITNOT,       "'~'") \
    \
    macro(ARROW,        "'=>'")   /* function arrow */ \
    \
    /* Assignment ops, per TokenKindIsAssignment */ \
    macro(ASSIGN,       "'='") \
    range(ASSIGNMENT_START, ASSIGN) \
    macro(ADDASSIGN,    "'+='") \
    macro(SUBASSIGN,    "'-='") \
    macro(BITORASSIGN,  "'|='") \
    macro(BITXORASSIGN, "'^='") \
    macro(BITANDASSIGN, "'&='") \
    macro(LSHASSIGN,    "'<<='") \
    macro(RSHASSIGN,    "'>>='") \
    macro(URSHASSIGN,   "'>>>='") \
    macro(MULASSIGN,    "'*='") \
    macro(DIVASSIGN,    "'/='") \
    macro(MODASSIGN,    "'%='") \
    macro(POWASSIGN,    "'**='") \
    range(ASSIGNMENT_LAST, POWASSIGN)

#define TOKEN_KIND_RANGE_EMIT_NONE(name, value)
#define FOR_EACH_TOKEN_KIND(macro) \
    FOR_EACH_TOKEN_KIND_WITH_RANGE(macro, TOKEN_KIND_RANGE_EMIT_NONE)

namespace js {
namespace frontend {

// Values of this type are used to index into arrays such as isExprEnding[],
// so the first value must be zero.
enum TokenKind {
#define EMIT_ENUM(name, desc) TOK_##name,
#define EMIT_ENUM_RANGE(name, value) TOK_##name = TOK_##value,
    FOR_EACH_TOKEN_KIND_WITH_RANGE(EMIT_ENUM, EMIT_ENUM_RANGE)
#undef EMIT_ENUM
#undef EMIT_ENUM_RANGE
    TOK_LIMIT                      // domain size
};

inline bool
TokenKindIsBinaryOp(TokenKind tt)
{
    return TOK_BINOP_FIRST <= tt && tt <= TOK_BINOP_LAST;
}

inline bool
TokenKindIsEquality(TokenKind tt)
{
    return TOK_EQUALITY_START <= tt && tt <= TOK_EQUALITY_LAST;
}

inline bool
TokenKindIsRelational(TokenKind tt)
{
    return TOK_RELOP_START <= tt && tt <= TOK_RELOP_LAST;
}

inline bool
TokenKindIsShift(TokenKind tt)
{
    return TOK_SHIFTOP_START <= tt && tt <= TOK_SHIFTOP_LAST;
}

inline bool
TokenKindIsAssignment(TokenKind tt)
{
    return TOK_ASSIGNMENT_START <= tt && tt <= TOK_ASSIGNMENT_LAST;
}

inline MOZ_MUST_USE bool
TokenKindIsKeyword(TokenKind tt)
{
    return (TOK_KEYWORD_FIRST <= tt && tt <= TOK_KEYWORD_LAST) ||
           (TOK_KEYWORD_BINOP_FIRST <= tt && tt <= TOK_KEYWORD_BINOP_LAST) ||
           (TOK_KEYWORD_UNOP_FIRST <= tt && tt <= TOK_KEYWORD_UNOP_LAST);
}

inline MOZ_MUST_USE bool
TokenKindIsContextualKeyword(TokenKind tt)
{
    return TOK_CONTEXTUAL_KEYWORD_FIRST <= tt && tt <= TOK_CONTEXTUAL_KEYWORD_LAST;
}

inline MOZ_MUST_USE bool
TokenKindIsFutureReservedWord(TokenKind tt)
{
    return TOK_FUTURE_RESERVED_KEYWORD_FIRST <= tt && tt <= TOK_FUTURE_RESERVED_KEYWORD_LAST;
}

inline MOZ_MUST_USE bool
TokenKindIsStrictReservedWord(TokenKind tt)
{
    return TOK_STRICT_RESERVED_KEYWORD_FIRST <= tt && tt <= TOK_STRICT_RESERVED_KEYWORD_LAST;
}

inline MOZ_MUST_USE bool
TokenKindIsReservedWordLiteral(TokenKind tt)
{
    return TOK_RESERVED_WORD_LITERAL_FIRST <= tt && tt <= TOK_RESERVED_WORD_LITERAL_LAST;
}

inline MOZ_MUST_USE bool
TokenKindIsReservedWord(TokenKind tt)
{
    return TokenKindIsKeyword(tt) ||
           TokenKindIsFutureReservedWord(tt) ||
           TokenKindIsReservedWordLiteral(tt);
}

inline MOZ_MUST_USE bool
TokenKindIsPossibleIdentifier(TokenKind tt)
{
    return tt == TOK_NAME ||
           TokenKindIsContextualKeyword(tt) ||
           TokenKindIsStrictReservedWord(tt);
}

inline MOZ_MUST_USE bool
TokenKindIsPossibleIdentifierName(TokenKind tt)
{
    return TokenKindIsPossibleIdentifier(tt) ||
           TokenKindIsReservedWord(tt);
}

} // namespace frontend
} // namespace js

#endif /* frontend_TokenKind_h */
