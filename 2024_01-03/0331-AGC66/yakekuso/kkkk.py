def main():
    n = int(input())  # 標準入力から整数を読み込む
    five = [1] * (n + 1)  # 5のべき乗を格納するリストを初期化
    for i in range(n):
        five[i + 1] = five[i] * 5
    
    with open("FiveOutFile.txt", "w") as fout:  # ファイルを開き、変数foutにバインド
        for i in range(n + 1):
            s = str(five[i])  # 数値を文字列に変換
            ans = sum(int(char) for char in s)  # 文字列の各文字を整数に変換し、合計を計算
            fout.write(f"{ans}\n")  # ファイルに書き込み

if __name__ == "__main__":
    main()
