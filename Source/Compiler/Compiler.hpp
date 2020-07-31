
#include "../Common/Header.hpp"

#ifndef SPIN_COMPILER_HPP
#define SPIN_COMPILER_HPP

#include <unordered_map>

#include "../Token/Token.hpp"

#include "Program.hpp"

#include "../Utility/Stack.hpp"

using Unary = UInt16;
using Binary = UInt32;

namespace Spin {

	enum Precedence : UInt8 {
		none,
		assignment,
		logicOR,
		logicAND,
		bitwiseOR,
		bitwiseXOR,
		bitwiseAND,
		equality,
		comparison,
		term,
		factor,
		unary,
		call,
		primary,
	};

	class Compiler {

		private:

		typedef void (Compiler::*ParseFunction)();

		struct ParseRule {
			ParseFunction prefix = nullptr;
			ParseFunction infix = nullptr;
			Precedence precedence = Precedence::none;
		};

		struct Local {
			String name;
			SizeType depth = 0;
			Type type;
			Boolean ready = false;
		};
		struct Global {
			SizeType index;
			Type type;
			Boolean ready = false;
		};

		struct Jump {
			SizeType line = 0;
			SizeType scope = 0;
		};

		struct Routine {
			String name;
			Type returnType = Type::VoidType;
			Array<Type> parameters;
			Array<ByteCode> code;
			Boolean returns = false;
			SizeType scope;
		};

		Array<Routine> routines;

		Array<Local> locals;
		SizeType scopeDepth = 0;

		static const Dictionary<Token::Type, ParseRule> rules;

		Program * program = nullptr;
		Token current;
		Token previous;
		SizeType index = 0;
		CodeUnit * currentUnit = nullptr;
		Array<Token> * tokens = nullptr;

		Stack<Type> typeStack;
		Stack<Boolean> assignmentStack;
		Stack<SizeType> cycleScopes;
		Stack<SizeType> routineIndexes;
		Stack<Jump> breakStack;
		Stack<Jump> continueStack;

		Dictionary<String, SizeType> strings;

		static const Dictionary<Binary, Type> infixTable;
		static const Dictionary<Unary, Type> prefixTable;
		static const Dictionary<Unary, Type> postfixTable;
		static const Dictionary<Types, Boolean> castTable;

		static consteval Unary compose(Token::Type token, Type type) {
			return (Unary)(((Unary) token << 8) | type);
		}
		static consteval Binary compose(Token::Type token, Type a, Type b) {
			return (Binary)(((Binary) a << 16) | ((Binary) token << 8) | b);
		}
		static consteval Types compose(Type a, Type b) {
			return (Types)(((Types) a << 8) | b);
		}

		ParseRule getRule(Token::Type token);

		static inline Unary runtimeCompose(Token::Type token, Type type) {
			return (Unary)(((Unary) token << 8) | type);
		}
		static inline Binary runtimeCompose(Token::Type token, Type a, Type b) {
			return (Binary)(((Binary) a << 16) | ((Binary) token << 8) | b);
		}
		static inline Types runtimeCompose(Type a, Type b) {
			return (Types)(((Types) a << 8) | b);
		}

		void booleanLiteral();
		void characterLiteral();
		void stringLiteral();
		void imaginaryLiteral();
		void realLiteral();
		void realIdioms();
		void integerLiteral();

		void expression();
		void statement();
		void declaration();
		void variable();
		void identifier();
		void block();

		void logicAND();
		void logicOR();

		void grouping();
		void cast();
		void call();
		void ternary();
		void postfix();
		void binary();
		void prefix();

		void expressionStatement();
		void printStatement();
		void ifStatement();
		void whileStatement();
		void untilStatement();
		void doWhileStatement();
		void repeatUntilStatement();
		void loopStatement();
		void forStatement();
		void breakStatement();
		void continueStatement();
		void procStatement();
		void funcStatement();
		void returnStatement();
		void swapStatement();

		SizeType resolve(String & name, Local & local);

		void parsePrecedence(Precedence precedence);

		inline Boolean match(Token::Type type);
		inline Boolean matchAssignment();
		inline Boolean check(Token::Type type);
		inline void advance();
		inline void consume(Token::Type type, String lexeme);
		inline void resolveRoutines();
		inline SizeType countLocals(SizeType scope);
		inline SizeType sourcePosition();
		inline void emitException(Program::Error error);
		inline void emitOperation(ByteCode code);
		inline void emitOperation(OPCode code);
		inline void emitString(String s);
		inline void emitJMB(SizeType jmb);
		inline SizeType emitJMP(OPCode code);
		inline void patchJMP(SizeType jmp);
		inline void patchJMB(SizeType pos, SizeType jmb);
		inline void patchOP(SizeType op, OPCode code);
		inline Array<ByteCode> cutCodes(SizeType cut);
		inline void pasteCodes(Array<ByteCode> codes);
		inline void beginScope();
		inline void beginVirtualScope();
		inline void endScope();
		inline void endVirtualScope();
		inline SizeType emitRST();
		inline void emitPOP(SizeType n);
		inline void emitRET();
		inline void emitHLT();

		void reset();

		Compiler() = default; ~Compiler() = default;

		public:

		Compiler(const Compiler &) = delete;
		Compiler(Compiler &&) = delete;
		Compiler & operator = (const Compiler &) = delete;
		Compiler & operator = (Compiler &&) = delete;
		inline static Compiler * self() {
			static Compiler instance;
			return & instance;
		}
		Program * compile(SourceCode * source);

	};

}

#endif
