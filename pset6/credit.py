'''
    Author: Jakub Rupinski
    Excersize from pset6, for CS50 MOOC

    Program takes credit card number from user and says if it's valid or not
'''


def main():

    # test cases
    # VISA
    isValid("4012888888881881")
    # MasterCard
    isValid("5555555555554444")
    # AMEX
    isValid("378282246310005")
    # INVALID
    isValid("6176292929")
    # USER INPUT
    creditCard = getCardNumber()
    isValid(creditCard)


def getCardNumber():

    while True:
        cardNumber = input("Input your credit card number: ")
        # if number length is not valid for VISA, AMEX or MasterCard  - retry
        if (cardNumber.isdigit()) and (len(cardNumber) in [13, 15, 16]):
            break
        print("Not a valid card number, retry...")

    return cardNumber


def isValid(card):

    # keep sums of both multiplied and un-multiplied digits
    sumOfMultiplied = 0
    sumOfNotMultiplied = 0
    sumTotal = 0

    # calculate end point for the for loop
    if len(card) % 2 == 0:
        end = -1
    else:
        end = 0

    # multiply every other digit by 2, starting from second-to-last
    for i in range(len(card) - 2, end, -2):
        digitMultiplied = int(card[i]) * 2
        # add product's digits (not digits themselves) if number has >1 digit
        if digitMultiplied >= 10:
            # add ones
            sumOfMultiplied += int(digitMultiplied % 10)
            # add tens
            sumOfMultiplied += int(digitMultiplied / 10)
        else:
            sumOfMultiplied += digitMultiplied

    # sum non-multiplied digits
    for i in range(abs(end), len(card), 2):
        sumOfNotMultiplied += int(card[i])

    # add both sums and check if card is valid (last digit of total sum == 0)
    sumTotal = sumOfMultiplied + sumOfNotMultiplied
    if sumTotal % 10 == 0:
        getCardBrand(card)
    else:
        print("CHECKSUM INVALID")


def getCardBrand(card):

    firstTwoDigits = int(card[:2])
    # MasterCard numbers all start with 51, 52, 53, 54, or 55
    if firstTwoDigits in [51, 52, 53, 54, 55]:
        print("MASTERCARD")
    # American Express numbers all start with 34 or 37
    elif firstTwoDigits in [34, 37]:
        print("AMEX")
    # Visa numbers all start with 4
    elif int(card[0]) == 4:
        print("VISA")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()
