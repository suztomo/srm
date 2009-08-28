#!/usr/bin/python

def main():
    coins = [1, 5, 10, 50, 100, 500, 1000, 2000, 5000, 10000]
    dp = range(10001)
    for i in range(10001):
        dp[i] = 0
    dp[1] = 1
    for i in range(2, 10001):
        for c in coins:
            if (i - c) > 0:
                dp[i] += dp[i-c]
            elif i == c:
                dp[i] += 1
        print(str(i) + ": " + str(dp[i]) + "\n")
        import pdb; pdb.set_trace()
    print(dp[10000])

if __name__ == "__main__":
    main()
