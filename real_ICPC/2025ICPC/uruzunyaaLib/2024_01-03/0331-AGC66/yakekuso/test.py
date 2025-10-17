def main():
    
    test = int(input())
    two = [1] * 51  # 配列の初期化
    for i in range(50):
        two[i + 1] = two[i] * 2
    five = [1] * 100001  # 配列の初期化
    for i in range(100000):
        five[i + 1] = five[i] * 5
    for i in range(50):
        tmp = five[test] * two[i]
        st = str(tmp)
        fx = sum(int(char) for char in st)  # 文字列の各文字を整数に変換して合計
        print(f"{tmp} {fx}")

if __name__ == "__main__":
    main()
