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
    for i in range(ord('a'), ord('z')):
        currString = chr(i)
        hashed = crypt.crypt(currString, salt)
        if hashed == encryptedText:
            print(currString)
            break


if __name__ == '__main__':
    main()
