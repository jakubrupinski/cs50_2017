import sys
import crypt
import string
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
    for i in range(0, len(string.ascii_letters)):
        currString = string.ascii_letters[i]
        hashed = crypt.crypt(currString, salt)
        if hashed == encryptedText:
            print(currString)
            exit(0)

    # Check for 2-char password
    for i in range(0, len(string.ascii_letters)):
        for j in range(0, len(string.ascii_letters)):
            currString = string.ascii_letters[i] + string.ascii_letters[j]
            hashed = crypt.crypt(currString, salt)
            if hashed == encryptedText:
                print(currString)
                exit(0)

    # Check for 3-char password
    for i in range(0, len(string.ascii_letters)):
        for j in range(0, len(string.ascii_letters)):
            for k in range(0, len(string.ascii_letters)):
                currString = string.ascii_letters[i]
                + string.ascii_letters[j]
                + string.ascii_letters[k]
                hashed = crypt.crypt(currString, salt)
                if hashed == encryptedText:
                    print(currString)
                    exit(0)

    # Check for 4-char password
    for i in range(0, len(string.ascii_letters)):
        for j in range(0, len(string.ascii_letters)):
            for k in range(0, len(string.ascii_letters)):
                for l in range(0, len(string.ascii_letters)):
                    currString = string.ascii_letters[i]
                    + string.ascii_letters[j]
                    + string.ascii_letters[k]
                    + string.ascii_letters[l]
                    hashed = crypt.crypt(currString, salt)
                    if hashed == encryptedText:
                        print(currString)
                        exit(0)


if __name__ == '__main__':
    main()
