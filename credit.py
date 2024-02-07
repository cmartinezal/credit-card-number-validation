from cs50 import get_string


def get_first_two_digits(number: str) -> int:
    """
    Get first two digits of a number
    """
    first_digits = f'{number[0]}{number[1]}'
    return int(first_digits)


def is_valid_digit_count(card_number: str) -> bool:
    """
    Validate credit card number of digits
    """
    digits = len(card_number)
    digit_list = [13, 15, 16]

    return digits in digit_list


def get_card_company(card_number: str) -> str:
    """
    Get credit card company based on credit card number
    """
    first_digits = get_first_two_digits(card_number)

    is_amex = first_digits == 34 or first_digits == 37
    is_mastercard = first_digits >= 51 and first_digits <= 55
    is_visa = first_digits >= 40 and first_digits <= 49

    digits = len(card_number)
    digit_dict = {'AMEX': [15], 'MASTERCARD': [16], 'VISA': [13, 16]}
    company = 'INVALID'

    if is_amex and digits in digit_dict['AMEX']:
        company = 'AMEX'
    elif is_mastercard and digits in digit_dict['MASTERCARD']:
        company = 'MASTERCARD'
    elif is_visa and digits in digit_dict['VISA']:
        company = 'VISA'

    return company


def luns_algorithm_validation(card_number: str) -> bool:
    """
    Validate credit card number based on luhn's algorithm
    """
    even_sum = 0
    odd_sum = 0

    reversed_card_num = card_number[::-1]

    for index, digit in enumerate(reversed_card_num):
        is_even_pos = (index + 1) % 2 == 0

        if is_even_pos:
            product = str(int(digit) * 2)
            even_sum += sum(list(map(int, product)))
        else:
            odd_sum += int(digit)

    checksum = even_sum + odd_sum

    return checksum % 10 == 0


def validate_credit_card() -> None:
    """
    Validate credit card number and prints the compay
    """
    card_number = get_string("Number: ")

    if not is_valid_digit_count(card_number):
        print("INVALID")
        return 0

    if not luns_algorithm_validation(card_number):
        print("INVALID")
        return 0

    company = get_card_company(card_number)
    print(f'{company}')


if __name__ == "__main__":
    validate_credit_card()
