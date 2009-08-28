#!/usr/bin/python

def main():
    years = 3000 - 2001 + 1
    # Luckly, 2000 is divisible by 4, 100, 400
    print((365 * years + (1000/4) - (1000/100) + (1000/400)) / 7)

if __name__ == "__main__":
    main()
