import sys
import crypt
import string
import itertools


def main():
    # sanity check
    if(len(sys.argv) != 2):
        print("Usage: ./crack hash")
        exit(1)

    # take user parameter as encrypted password to crack
    encrypted = sys.argv[1]
    decrypt(encrypted, 4)


def decrypt(encryptedText, pwdlength):
    # first two characters equall salt
    salt = encryptedText[:2]

    charset = string.ascii_letters

    # this generates every combination of given letters for hash checking
    # thanks to ecatmur from StackOverflow for this line!
    generator = itertools.chain. \
        from_iterable((''.join(l)
                       for l in itertools.product(charset, repeat=i))
                      for i in range(1, pwdlength + 1))

    for password in generator:
            hashed = crypt.crypt(str(password), salt)

            # if found - print password and exit
            if hashed == encryptedText:
                print(password)
                exit(0)

    print("Hash incorrect or password longer than 4 characters!")


if __name__ == '__main__':
    main()
