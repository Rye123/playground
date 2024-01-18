from enum import IntEnum
from typing import List, Any, Union
from dataclasses import dataclass

DEBUG = True
WHITESPACE = [" ", "\t"]

def dbgprint(msg: str):
    if DEBUG:
        print(msg)

class TokenType(IntEnum):
    NUMBER = 0
    PLUS = 1
    MINUS = 2
    STAR = 3
    SLASH = 4
    EOF = 5

@dataclass
class Token:
    type: TokenType
    value: str
    literal: Any

    def __repr__(self) -> str:
        return f"<{TokenType(self.type).name}, {self.value}>"

class SyntaxError(Exception):
    def __init__(self, msg: str):
        return super().__init__(f"Syntax Error: {msg}")

def tokenise(source: str) -> List[Token]:
    """ Tokenises a string of source code into a list of tokens """
    tokens = []
    ptr = 0
    cur_lexeme = ""
    while True:
        match source[ptr]:
            case '+':
                tokens.append(Token(TokenType.PLUS, "+", None))
            case '-':
                tokens.append(Token(TokenType.MINUS, "-", None))
            case '*':
                tokens.append(Token(TokenType.STAR, "*", None))
            case '/':
                tokens.append(Token(TokenType.SLASH, "/", None))
            case _:
                if source[ptr] in WHITESPACE:
                    pass
                elif source[ptr].isdigit():
                    cur_lexeme = ""
                    
                    # Parse the rest of the number
                    while ptr < len(source) and source[ptr].isdigit():
                        cur_lexeme += source[ptr]
                        ptr += 1
                    
                    if ptr < len(source) and source[ptr] == '.':
                        # Here, we've parsed up till the start of a float
                        cur_lexeme += source[ptr]
                        ptr+=1
                        # Parse the rest of the number
                        while ptr < len(source) and source[ptr].isdigit():
                            cur_lexeme += source[ptr]
                            ptr += 1

                    # Here, we've parsed up till the end of a number
                    ptr -= 1
                    tokens.append(Token(TokenType.NUMBER, cur_lexeme, float(cur_lexeme)))
                else:
                    raise SyntaxError(f"Invalid character {source[ptr]}")

        ptr += 1
        if ptr == len(source):
            break

    tokens.append(Token(TokenType.EOF, None, None))
    return tokens

class SymbolType(IntEnum):
    EXPRESSION = 0
    EXPRESSION_R = 1
    TERM = 2
    TERM_R = 3
    UNARY = 4
    TERMINAL = 5

class Symbol:
    def __init__(self, type: SymbolType, value: Union[None, Token] = None):
        self.type = type
        self.value = value

    def __repr__(self) -> str:
        print("ree")
        return self.type.name
    
class ParseTreeNode:
    def __init__(self, symbol: Symbol, parent: Union['ParseTreeNode', None] = None):
        self.type = symbol.type
        self.symbol = symbol
        self.parent = parent
        self.children: List[Union['ParseTreeNode', None]] = []

    def add_child(self, symbol: Symbol):
        self.children.append(ParseTreeNode(symbol, self))
        return self.children[-1]

    def add_child_u(self, symbol_type: SymbolType):
        """ Add an unexpanded child node """
        self.children.append(ParseTreeNode(Symbol(symbol_type), self))
        return self.children[-1]

    def evaluate(self) -> str:
        if self.type == SymbolType.TERMINAL:
            return self.symbol.value.value
        else:
            ret_str = ""
            if len(self.children) == 0:
                return ""
            
            for child in self.children:
                ret_str += child.evaluate() + " "
            
            return f"({ret_str.strip()})"
                
                

    def __repr__(self) -> str:
        if self.type == SymbolType.TERMINAL:
            if self.symbol.value is None:
                return "None"
            return self.symbol.value.type.name

        if len(self.children) == 0:
            return ""
        
        ret_child = ""
        for child in self.children:
            ret_child += "NA" if child is None else child.__repr__()
            ret_child += " "

        ret_child = ret_child.strip()
        #return f"{self.symbol.type.name}({ret_child})"
        return f"({ret_child})"

class ParseTree:
    def __init__(self):
        self.root = ParseTreeNode(Symbol(SymbolType.EXPRESSION))

    def __repr__(self) -> str:
        return self.root.__repr__()

class ParseError(Exception):
    def __init__(self, msg: str):
        super().__init__(f"ParseError: {msg}")

class Parser:
    def __init__(self, tokens: List[Token]):
        self.tokens = tokens
        self.tree = ParseTree()
        self.ptr = 0

    def advance(self) -> None:
        """ Advances the pointer. """
        self.ptr += 1

    def peek(self) -> Token:
        """ Returns the next unconsumed token. """
        return self.tokens[self.ptr+1]

    def parse(self) -> ParseTree:
        while True:
            token = self.tokens[self.ptr]
            if token.type == TokenType.EOF:
                return self.tree

            # Step 1: Expansion of Nonterminal
            # We select a production rule for the given token
            # Note: For each parse_ procedure, the parent constructs the tree_ptr and the procedure fills up the children.
            self.parse_expression(self.tree.root)

    def parse_number(self, node: ParseTreeNode):
        lookahead = self.tokens[self.ptr]
        dbgprint(f"parse_number: {lookahead}, {node}")
        assert node.type == SymbolType.TERMINAL
        
        # Only valid value is a number
        if lookahead.type == TokenType.NUMBER:
            node.symbol = Symbol(SymbolType.TERMINAL, lookahead)
            self.advance()
            return
        raise ParseError(f"ParseError: Token {lookahead} is not a number")

    def parse_unary(self, node: ParseTreeNode):
        lookahead = self.tokens[self.ptr]
        dbgprint(f"parse_unary: {lookahead}, {node}")
        assert node.type == SymbolType.UNARY
        
        # FIRST(tokens) is +/- or a number
        if lookahead.type == TokenType.PLUS or lookahead.type == TokenType.MINUS:
            # Construct tree based on production
            node.add_child(Symbol(SymbolType.TERMINAL, lookahead))
            self.advance()
            number_node = node.add_child_u(SymbolType.TERMINAL)
            self.parse_number(number_node)
            return
        elif lookahead.type == TokenType.NUMBER:
            number_node = node.add_child_u(SymbolType.TERMINAL)
            self.parse_number(number_node)
            return
        raise ParseError(f"ParseError: Invalid lookahead token {lookahead} for unary expression")

    def parse_term_r(self, node: ParseTreeNode):
        lookahead = self.tokens[self.ptr]
        dbgprint(f"parse_term_right: {lookahead}, {node}")
        assert node.type == SymbolType.TERM_R

        # FIRST(tokens) is * or /, otherwise it's empty
        if lookahead.type == TokenType.STAR or lookahead.type == TokenType.SLASH:
            node.add_child(Symbol(SymbolType.TERMINAL, lookahead))
            self.advance()
            term_node = node.add_child_u(SymbolType.TERM)
            self.parse_term(term_node)
            term_r_node = node.add_child_u(SymbolType.TERM_R)
            self.parse_term_r(term_r_node)
            return
        return True # empty

    def parse_term(self, node: ParseTreeNode):
        lookahead = self.tokens[self.ptr]
        dbgprint(f"parse_term: {lookahead}, {node}")
        assert node.type == SymbolType.TERM

        # FIRST(tokens) is a unary
        unary_node = node.add_child_u(SymbolType.UNARY)
        self.parse_unary(unary_node)
        term_r_node = node.add_child_u(SymbolType.TERM_R)
        self.parse_term_r(term_r_node)

    def parse_expression_r(self, node: ParseTreeNode):
        lookahead = self.tokens[self.ptr]
        dbgprint(f"parse_expression_right: {lookahead}, {node}")
        assert node.type == SymbolType.EXPRESSION_R

        # FIRST(tokens) is * or /, otherwise it's empty
        if lookahead.type == TokenType.PLUS or lookahead.type == TokenType.MINUS:
            node.add_child(Symbol(SymbolType.TERMINAL, lookahead))
            self.advance()
            expr_node = node.add_child_u(SymbolType.EXPRESSION)
            self.parse_expression(expr_node)
            expr_r_node = node.add_child_u(SymbolType.EXPRESSION_R)
            self.parse_expression_r(expr_r_node)
            return
        return  # EMPTY

    def parse_expression(self, node: ParseTreeNode):
        lookahead = self.tokens[self.ptr]
        dbgprint(f"parse_expression: {lookahead}, {node}")
        assert node.type == SymbolType.EXPRESSION

        term_node = node.add_child_u(SymbolType.TERM)
        self.parse_term(term_node)
        expr_r_node = node.add_child_u(SymbolType.EXPRESSION_R)
        self.parse_expression_r(expr_r_node)

def main():
    try:
        while True:
            try:
                source = input("> ")
                tokens = tokenise(source)
                print(tokens)

                parser = Parser(tokens)
                print(parser.parse())

                string = parser.tree.root.evaluate()
                print(string)

            except SyntaxError as e:
                print(e)
            except ParseError as e:
                print(e)
    except KeyboardInterrupt:
        pass
    
if __name__ == "__main__":
    main()
                    
                
