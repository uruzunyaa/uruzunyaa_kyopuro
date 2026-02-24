from collections import deque, defaultdict
def apply(a1, a2, f):
    if f == "I":
        return a2 + 1
    if f == "T":
        return a2 * 2
    if f == "F":
        return a1 + a2
    assert False
def solve1(ml=10):
    # oo = 10**9
    # memo = defaultdict(lambda: (oo, []))
    memo = defaultdict(list)
    q = deque([(0, 1, "")])
    while q:
        a1, a2, s = q.popleft()
        if len(s) > ml:
            break
        for f in "ITF":
            if s and f == s[-1]:
                continue
            a3 = apply(a1, a2, f)
            ns = s + f
            memo[a3].append(ns)
            q.append((a2, a3, ns))
    for k, v in memo.items():
        print(k, ">", *v)

def to3(n):
    s = []
    while n:
        n, r = divmod(n, 3)
        s.append(r)
    return s

def show(s):
    a = [0, 1]
    for si in s:
        if si == "I":
            a.append(a[-1] + 1)
        if si == "T":
            a.append(a[-1] * 2)
        if si == "F":
            a.append(a[-2] + a[-1])
        print(si, a[-1], "\t", "".join(str(x) for x in to3(a[-1])))
solve1(5)
