"""
    Excersize for pset 8 in CS50 MOOC
    Author: Jakub Rupinski

    Program for printing out Super Mario Bros' "pyramids" in console
    The height of a pyramid is given by the user when the program is run 
"""
def main():
    height = getHeight()
    print_pyramid(height)


def getHeight():
    while True:
        height = input("Input pyramid height(lower than 24): ")
        # if input is not a digit - retry until an int is given
        if height.isdigit():
            height = int(height)
            # if input is in range - break loop and return height
            if height > 0 and height < 24:
                break

        print("Incorrect input, retry...")

    return height


def print_pyramid(height):
    # print each horizontal line - indexing starts at 1 to print first line
    for i in range(1, height + 1):

        # print left half of pyramid
        print((height - i) * " ", end="")
        print(i * "#", end="")
        # separate two halves with two spaces 
        print(2 * " ", end="")
        # print right half of pyramid
        print(i * "#")


# execute main function
if __name__ == "__main__":
    main()