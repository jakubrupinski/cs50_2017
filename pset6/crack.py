import sys
import crypt

# a = aa0wSaCDPDEl2


def main():
    if(len(sys.argv) != 2):
        print("Usage: ./crack hash")
        exit(1)

    encrypted = sys.argv[1]
    decrypt(encrypted)


def decrypt(encryptedText):
    # first two characters is salt
    salt = encryptedText[:2]

    # Check for 1-char password
    for i in range(ord('a'), ord('z')):
        currString = chr(i)
        hashed = crypt.crypt(currString, salt)
        if hashed == encryptedText:
            print(currString)
            exit(0)

    # Check for 2-char password
    for i in range(ord('a'), ord('z')):
        for j in range(ord('a'), ord('z')):
            currString = chr(i) + chr(j)
            hashed = crypt.crypt(currString, salt)
            if hashed == encryptedText:
                print(currString)
                exit(0)

    # Check for 3-char password
    for i in range(ord('a'), ord('z')):
        for j in range(ord('a'), ord('z')):
            for k in range(ord('a'), ord('z')):
                currString = chr(i) + chr(j) + chr(k)
                hashed = crypt.crypt(currString, salt)
                if hashed == encryptedText:
                    print(currString)
                    exit(0)

    # Check for 4-char password
    for i in range(ord('a'), ord('z')):
        for j in range(ord('a'), ord('z')):
            for k in range(ord('a'), ord('z')):
                for l in range(ord('a'), ord('z')):
                    currString = chr(i) + chr(j) + chr(k) + chr(l)
                    hashed = crypt.crypt(currString, salt)
                    if hashed == encryptedText:
                        print(currString)
                        exit(0)


if __name__ == '__main__':
    main()
