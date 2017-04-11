def main():
    creditCard = getCardNumber()
    print(creditCard)

def getCardNumber():
    while True:
        cardNumber = input("Input your credit card number: ")
        # if number length is not valid for VISA, AMEX or MasterCard  - retry
        if (cardNumber.isdigit()) and (len(cardNumber) in [13, 15, 16] )  :
            break

        print("Not a valid card number, retry...")

    return cardNumber

if __name__ == "__main__":
    main()