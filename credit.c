#include <cs50.h>
#include <stdio.h>

// All the functions used.
long long get_crd(void);
int luhnAlgrtm(long long crd, int cnt);
int cntDigt(long long crd);
int frstchk(int cont);
int scndchk(long long crd, int cont);
int trdchk(long long crd, int cont);
int get_frst2digt(long long crd);
int fullchk(long long crd, int cont);
void dsplyrslt(int v);

int main(void)
{
    long long crd = 0;
    int crdchk = 0;
    int cont = 0;

    crd = get_crd();             // user inputs the card number.
    cont = cntDigt(crd);         // counting the number of digits.
    crdchk = fullchk(crd, cont); // verify if input correct and which card.
    dsplyrslt(crdchk);           // display final result.
}

long long get_crd(void)
{
    long long crd = 0;
    printf("Number: ");
    scanf("%lld", &crd); // user inputs the card details
    return crd;
}

// A function that calls all the different validity check functions.
int fullchk(long long crd, int cont)
{
    int crdchk = 0;
    if (crdchk == 0)
    {
        // first validity check: if the no. of digits is equal to 13, 15 or 16
        crdchk = frstchk(cont);
        // printf("fchk: %d\n", crdchk);
    }
    if (crdchk == 0)
    {
        // second validity check: uses Luhn's algorithms to check validity
        crdchk = scndchk(crd, cont);
        // printf("schk: %d\n", crdchk);
    }
    if (crdchk == 0)
    {
        /*
        third validity check: checks which card using the first two digits
        returns int
        1 - American Express
        2 - MasterCard
        3 - Visa
        */
        crdchk = trdchk(crd, cont);
    }
    return crdchk;
}

// Counts and returns total number of dights.
int cntDigt(long long crd)
{
    int cont = 0;
    while (crd)
    {
        crd /= 10;
        cont++;
    }
    return cont;
}

// Checks to see if the no. of digits is an expected value, i.e. either 13, 15 or 16
int frstchk(int cont)
{
    if (cont == 13 || cont == 15 || cont == 16)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

// Checks using Luhn algorithm. checks if the last digit of the returnd value is 0.
int scndchk(long long crd, int cont)
{
    int La = luhnAlgrtm(crd, cont);
    // Return 0 if valid or -1 if invalid
    if (La % 10 == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

// Returns based on the first two digits of the credit card.
// Checks if the starting numbers are of Visa, AMEX or mastercard
int trdchk(long long crd, int cont)
{
    int ch = get_frst2digt(crd);
    if (cont == 13)
    {
        if (ch / 10 == 4)
        {
            return 3; // its visa
        }
    }
    else if (cont == 15)
    {
        if (ch == 34 || ch == 37)
        {
            return 1; // its american express
        }
    }
    else if (cont == 16)
    {
        if (ch / 10 == 4)
        {
            return 3; // its visa
        }
        else if (ch == 51 || ch == 52 || ch == 53 || ch == 54 || ch == 55)
        {
            return 2; // its mastercard
        }
    }
    return -1;
}

// Returns the first two digits of the crdit card.
int get_frst2digt(long long crd)
{

    while (crd >= 100)
    {
        crd /= 10;
    }

    return crd;
}

// Calculates the Luhn Algorithem and returns the result
int luhnAlgrtm(long long crd, int cnt)
{
    long long temp = crd;
    int c = 0;
    int La = 0;
    long long temp2 = 0;
    long long temp3 = 0;
    int n = 0;

    for (int x = 0; x <= (cnt); x++)
    {

        c = temp % 10;
        temp /= 10;

        if (x % 2 != 0)
        {
            c *= 2;
        }

        if (n < cnt / 2)
        {
            while (c)
            {
                temp2 *= 10;
                temp2 += (c % 10);
                // printf("adding c = %d to temp2: %lld\n", c, temp2);
                c /= 10;
                n++;
            }
        }
        else
        {
            while (c)
            {
                temp3 *= 10;
                temp3 += (c % 10);
                // printf("adding c = %d to temp3: %lld\n", c, temp3);
                c /= 10;
                n++;
            }
        }
    }

    while (temp2)
    {
        La += temp2 % 10;
        temp2 /= 10;
    }
    while (temp3)
    {
        La += temp3 % 10;
        temp3 /= 10;
    }

    return La;
}

// A function to display the result
void dsplyrslt(int v)
{
    if (v == -1)
    {
        printf("INVALID\n");
    }
    else if (v == 0)
    {
        printf("Something went horribly wrong\n");
    }
    else if (v == 1)
    {
        printf("AMEX\n");
    }
    else if (v == 2)
    {
        printf("MASTERCARD\n");
    }
    else if (v == 3)
    {
        printf("VISA\n");
    }
    else
    {
        printf("Who even cares about some random credit validity check code? I give up\n");
    }
}
