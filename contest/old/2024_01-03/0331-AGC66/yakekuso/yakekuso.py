import random

def main():
    n = int(input())  # 標準入力から整数を読み込む
    five = [1] * (n + 1)  # 5のべき乗を格納するリストを初期化
    for i in range(1, n + 1):
        five[i] = five[i - 1] * 5
    
    with open("yakekusoOutFile.txt", "w") as fout:  # ファイルを開いて出力
        fout.write(f"{five[n]}\n")

if __name__ == "__main__":
    main()
