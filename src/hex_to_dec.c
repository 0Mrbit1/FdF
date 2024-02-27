int ft_strlen(char *str)
{
    int i ;
    
    i =0;
    while(str[i])
    {
        i++;
    }
    return i;
}


int ft_power(int number , int power)
{
    int result;

    result = 1;

    while(power--)
        result = result*number;
    return result ; 
}

int convert_to_decimal(char *str)
{
    char    *hex_digits;
    int i;
    int j;
    int len;
    int decimal;
    
    len = ft_strlen(str) -1;
    i = 0; 
    j = 0;
    decimal = 0;
    hex_digits = "0123456789ABCDEF";

    while(len  > 1)
    {
        while (hex_digits[j])
        {
            if (hex_digits[j] == str[len])
            {
                decimal +=  j*ft_power(16,i);
                i++;
                break;
            }
            j++;
        }
        j =0;
        len--;
    }
    return decimal;
}