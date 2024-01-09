#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

int count_digits(long number);
int get_first_two_digits(long number);
bool is_valid_digit_count(long card_number);
char *get_card_company(long card_number);
bool luns_algorithm_validation(long card_number);

int main(void)
{
    long card_number = get_long("Number: ");

    if (is_valid_digit_count(card_number) == false)
    {
        printf("INVALID\n");
        return 0;
    }

    if (luns_algorithm_validation(card_number) == false)
    {
        printf("INVALID\n");
        return 0;
    }

    char *company = get_card_company(card_number);
    printf("%s\n", company);
}

int count_digits(long number)
{
    long digits = 0;
    while (number != 0)
    {
        number /= 10;
        digits++;
    }
    return digits;
}

int get_first_two_digits(long number)
{
    while (number >= 100)
    {
        number /= 10;
    }
    return number;
}

bool is_valid_digit_count(long card_number)
{
    int digits = count_digits(card_number);
    bool is_amex = digits == 15;
    bool is_mastercard = digits == 16;
    bool is_visa = digits == 13 || digits == 16;

    if (is_amex || is_mastercard || is_visa)
    {
        return true;
    }
    return false;
}

char *get_card_company(long card_number)
{
    int first_digits = get_first_two_digits(card_number);

    bool is_amex = first_digits == 34 || first_digits == 37;
    bool is_mastercard = first_digits >= 51 && first_digits <= 55;
    bool is_visa = first_digits >= 40 && first_digits <= 49;

    int digits = count_digits(card_number);

    char *company = "INVALID";

    if (is_amex && digits == 15)
    {
        company = "AMEX";
    }
    else if (is_mastercard && digits == 16)
    {
        company = "MASTERCARD";
    }
    else if (is_visa && (digits == 13 || digits == 16))
    {
        company = "VISA";
    }

    return company;
}

bool luns_algorithm_validation(long card_number)
{
    int even_sum = 0;
    int odd_sum = 0;
    int position = 1;

    while (card_number != 0)
    {
        int digit = card_number % 10;
        bool is_even_pos = position % 2 == 0;

        if (is_even_pos)
        {
            int product = digit * 2;
            while (product != 0)
            {
                even_sum += product % 10;
                product /= 10;
            }
        }
        else
        {
            odd_sum += digit;
        }
        card_number /= 10;
        position++;
    }

    int checksum = (even_sum + odd_sum);
    return checksum % 10 == 0;
}
