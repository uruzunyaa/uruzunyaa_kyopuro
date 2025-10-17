import sys
import os
import random

if len(sys.argv) != 4 or sys.argv[1] == "-h" or sys.argv[1] == "--help":
    print("Usage: python3 gen_testcase.py <testCnt> <testCode> <genCnt>")
    print("testCnt: AC判定をするテストケースの数")
    print("testCode: テストするファイルを実行するコマンド")
    print("    例: python test.py")
    print("genCnt: 生成するテストケースの数")
    exit(0)

testCnt = int(sys.argv[1])
testCode = sys.argv[2]
genCnt = int(sys.argv[3])

inPath = "testcases\\in"
outPath = "testcases\\out"
waPath = "testcases\\wa"
generatedCnt = 0
waCnt = 0

tempPath = "temp"

# Initialize
os.system(f"del {inPath}\\random*.txt")
os.system(f"del {outPath}\\random*.txt")
os.system(f"del {waPath}\\* /Q")

# Constants
E9 = 10 ** 9
E5 = 10 ** 5


# Generate testcases
def gen_random():
    N = random.randint(2, 2 * E5)
    M = random.randint(0, E9)
    A = []
    sum = 0
    cnt = 0
    for j in range(N):
        A.append(random.randint(-cnt, E9))
        cnt += A[-1]
        if M < cnt:
            sum += A[-1] - (cnt - M)
            cnt = M
        else:
            if 0 <= A[-1]:
                sum += A[-1]

    return N, M, A, sum


def gen_corner_max():
    N = 2 * E5
    M = E9
    A = []
    sum = 0
    cnt = 0
    for j in range(N):
        if (j % 2 == 0):
            A.append(E9)
        else:
            A.append(-E9)
        cnt += A[-1]
        if M < cnt:
            sum += A[-1] - (cnt - M)
            cnt = M
        else:
            if 0 <= A[-1]:
                sum += A[-1]

    return N, M, A, sum


def gen_corner_min():
    N = 2 * E5
    M = E9
    A = []
    sum = 0
    cnt = 0
    for j in range(N):
        A.append(1)
        cnt += A[-1]
        if M < cnt:
            sum += A[-1] - (cnt - M)
            cnt = M
        else:
            if 0 <= A[-1]:
                sum += A[-1]

    return N, M, A, sum


def gen_corner_zero():
    N = 2 * E5
    M = 0
    A = []
    sum = 0
    cnt = 0
    for j in range(N):
        A.append(random.randint(-cnt, E9))
        cnt += A[-1]
        if M < cnt:
            sum += A[-1] - (cnt - M)
            cnt = M
        else:
            if 0 <= A[-1]:
                sum += A[-1]

    return N, M, A, sum


# Run program
def run_program(N, M, A):
    global tempPath
    global testCode

    with open(f"{tempPath}.in", "w") as f:
        print(N, M, file=f)
        print(*A, file=f)

    os.system(f"{testCode} < {tempPath}.in > {tempPath}.out")
    with open(f"{tempPath}.out") as f:
        out = int(f.read())
    return out


def check_program(N, M, A, sum, generate=False, fileName="random"):
    global testCnt
    global genCnt
    global inPath
    global outPath
    global waPath
    global tempPath
    global waCnt
    global generatedCnt

    out = run_program(N, M, A)
    if out != sum:
        os.system(f"copy {tempPath}.in {waPath}\\{waCnt}.in.txt")
        with open(f"{waPath}\\{waCnt}.out.txt", "w") as f:
            print(sum, file=f)
        waCnt += 1
        print(f"WA: {sum} != {out}")
    else:
        if generate:
            os.system(f"copy {tempPath}.in {inPath}\\{fileName}{str(generatedCnt + 1).zfill(2) if "random" == fileName else ""}.txt")
            os.system(f"copy {tempPath}.out {outPath}\\{fileName}{str(generatedCnt + 1).zfill(2) if "random" == fileName else ""}.txt")
            generatedCnt += 1

    os.system(f"del {tempPath}.in")
    os.system(f"del {tempPath}.out")


# Main loop
for i in range(testCnt):
    toGen = testCnt % (testCnt / genCnt) == 0
    (N, M, A, sum) = gen_random()
    check_program(N, M, A, sum, toGen)
    print(f"Done: {i + 1} / {testCnt} ({(i + 1) / testCnt * 100:.1f}%)")
(N, M, A, sum) = gen_corner_max()
check_program(N, M, A, sum, True, "corner1")
(N, M, A, sum) = gen_corner_min()
check_program(N, M, A, sum, True, "corner2")
(N, M, A, sum) = gen_corner_zero()
check_program(N, M, A, sum, True, "corner3")

if waCnt == 0:
    print("All AC")
else:
    print(f"WA: {waCnt} / {testCnt}")
    print(f"AC: {testCnt - waCnt} / {testCnt}")
