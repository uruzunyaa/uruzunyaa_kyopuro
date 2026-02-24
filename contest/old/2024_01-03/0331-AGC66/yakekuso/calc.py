def main():
    two = [1] * 51
    for i in range(50):
        two[i + 1] = two[i] * 2

    five = [1] * 100001
    for i in range(100000):
        five[i + 1] = five[i] * 5
    
    for x in range(1000):
        fx = [0] * 51
        for i in range(51):
            tmp = five[x] * two[i]
            st = str(tmp)
            for j in st:
                fx[i] += int(j)
        
        f = True
        for i in range(6):
            if fx[i] <= fx[i + 1]:
                f = False
                break
        if f:
            print(five[x])

if __name__ == "__main__":
    main()
