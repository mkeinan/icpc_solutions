""" ICPC-1563 ::: SETI """


a = []

def f(k ,n, p):
    print(a)
    sum = 0
    for i in range(0, n):
        sum += (a[i] * (k ** i)) % p
        sum = sum % p
    return sum


def main():
    run_samples()


def run_samples():
    global a
    pass
    a = [8, 13, 9, 13, 4, 27, 18, 10, 12, 24, 15]
    p = 29
    for k in range(1, len(a) + 1):
        res = f(k, len(a), p)
        print(f"f({k}, {len(a)}, {p}) = {res}      => {chr(res + ord('a') - 1)}")


if __name__ == "__main__":
    main()

