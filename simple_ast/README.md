# simple_ast

A simple recursive descent parser in Python, to compute simple infix expressions like "1 + 2 * 3".

**Grammar**:
```
E --> E + T | E - T | T    (E: Expression, T: Term)
T --> T * U | T / U | U    (T: Term, U: Unary)
U -->  + U  |  - U  | n    (U: Unary, n: number)
```

```
E   --> T E_R
E_R --> +/- E E_R | empty
T   --> U T_R
T_R --> *// T T_R | empty
U   --> +/- U     | n
```

## Usage
```bash
python3 simple_ast.py
```
