from sympy import sympify

# 標準入力で数式を受け取る
expression = input()

# sympifyで式を解析して評価

result = sympify(expression)
print(result)