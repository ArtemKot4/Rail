#ifndef TOKENTYPE_H
#define TOKENTYPE_H

enum TokenType {
	// function 
		// notations
	FUNCTION,			// function
	PROCEDURE,			// procedure

	// operators
	RETURN,				// return
	THROWS,				// throws
	DEFER,				// defer

	// threads
		// thread notations
	THREAD,				// thread

	// thread operations
	TRAIN,				// train
	YIELD,				// yield

	// object-oriented
		// create and delete objects
	NEW,				// new
	DELETE,				// delete

	// type data
	STRUCTURE,			// struct
	CLASS,				// class
	INTERFACE, 			// interface
	ENUMERATION, 		// enumeration
	UNIT,				// unit

	// access modifiers
	PUBLIC, 			// public
	PRIVATE, 			// private
	PROTECTED, 			// protected
	ABSTRACT, 			// abstract
	STATIC, 			// static

	NATIVE,				// native

	OPERATOR,			// operator
	KEYWORD,			// keyword

	// class and interface declarations and condition statements
	SATISFIES,          // satisfies
	EXTENDS,            // extends
	IMPLEMENTS,         // implements
	TYPEOF,				// typeof

	// object operators
	OF,                 // of
	IN,                 // in
	AS,                 // as

	// module
	NAMESPACE,			// namespace

	// condition statements
	IF,                 // if
	ELSE,               // else
	MATCH,              // match
	CASE,               // case

	// exception work
		// processing
	TRY,                // try
	CATCH,              // catch
	FINALLY,            // finally

	// calling
	THROW,              // throw

	// iterator
	ITERATOR, //iterator
		// loop notation
		FOR,                // for
		WHILE,              // while

	// operators
	BREAK,              // break
	CONTINUE,           // continue


	// variables
	LET,                // let
	CONST,              // const

	// operators
		// punctuation
	LEFT_PARENTHESIS,   // (
	RIGHT_PARENTHESIS,  // )
	LEFT_BRACE,         // {
	RIGHT_BRACE,        // }
	LEFT_BRACKET,       // [
	RIGHT_BRACKET,      // ]
	LEFT_ANGLE_BRACKET, // <
	RIGHT_ANGLE_BRACKET,// >

	SEMICOLON,          // ;
	COLON,              // :
	COMMA,              // ,
	POINT,              // .

	// additional
	DOG,                // @
	HASHTAG,            // #

	// arithmetic
	ASSIGN, 			// =
	ASSIGN_NULLABLE,    // ??=
	PLUS, 				// +	
	MINUS, 				// -
	STAR, 				// *
	SLASH, 				// /
	AMPERSAND, 			// &
	PIPE,				// |
	CARET,				// ^
	TILDE,				// ~
	DOLLAR,				// $
	PERCENT,			// %

	PLUS_ASSIGN,        // +=
	MINUS_ASSIGN,       // -=
	STAR_ASSIGN,        // *=
	SLASH_ASSIGN,       // /=
	PERCENT_ASSIGN,     // %=

	PLUS_PLUS,          // ++
	MINUS_MINUS,        // --

	// logical

	QUESTION_MARK,      // ?
	EXCLAMATION_MARK,   // !
	EQUAL_EQUAL,        // ==
	NOT_EQUAL,          // !=
	LESS_EQUAL,         // <=
	GREATER_EQUAL,      // >=

	AMPERSAND_AMPERSAND,// &&
	PIPE_PIPE,          // ||

	// object
	ELLIPSIS,           // ...
	ARROW,				// ->
	FAT_ARROW,			// =>

	STRING_LITERAL,     // strings like "string" or 'string'
	CHAR_LITERAL,       // characters like 'a'
	NUMBER_LITERAL,     // numbers like 123, 123.0, 0.123
	TRUE_LITERAL,       // true
	FALSE_LITERAL,      // false
	NULL_LITERAL,       // null

	// identifiers and keywords
	IDENTIFIER,		    // identifier
	STRING,             // string
	CHAR,			    // char
	INTEGER,            // int
	LONG,               // long
	FLOAT, 				// float
	DOUBLE,             // double
	BOOLEAN,            // boolean
	VOID,               // void
	UNKNOWN,			// unknown
	NUMBER,             // number

	// file
	IMPORT,             // import
	EXPORT,              // export,

	UNSUPPORTED
};

#endif