import sys
input = sys.stdin.readline

def main():
    T, C, K = map(int, input().strip().split())
    print((T * K) if (T * K) < C else C)
      
if __name__ == "__main__":
    main()
