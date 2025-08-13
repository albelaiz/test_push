#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <limits.h>

void ft_putchar(char c, int *counter)
{
    write (1, &c, 1);
    (*counter)++;
}

void ft_putnbr(int nb, int *counter)
{
    if (nb == -2147483648)
    {
        ft_putchar('-', counter);
        ft_putchar('2', counter);
        nb = 147483648;
    }
    if (nb < 0)
    {
         ft_putchar('-', counter);
         nb *= -1;
    }
    if (nb == 0)
    {
        ft_putchar('0', counter);
        return ;
    }
    if (nb > 9)
        ft_putnbr(nb / 10, counter);
    ft_putchar(nb % 10 + '0', counter);
}
void ft_puthex(unsigned int nb, char *base, int *counter)
{
    if (nb == 0)  // Handle the zero case
    {
        ft_putchar('0', counter);
        return;
    }
    if (nb > 15)
        ft_puthex(nb / 16, base,counter);
    ft_putchar(base[nb % 16], counter);
}
void ft_putstr(char *s, int *counter)
{
    if (!s)
        s = "(null)";
    while (*s)
        ft_putchar(*s++, counter);
}

int ft_printf(const char *format, ... )
{
    va_list list;
    int counter;
    va_start(list, format);
    counter = 0;
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            if (*format == 'c')
                ft_putchar((char)va_arg(list, int), &counter);
            else if (*format == 'd')
                ft_putnbr(va_arg(list, int), &counter);
            else if (*format == 'x')
                ft_puthex(va_arg(list, unsigned int), "0123456789abcdef",&counter);
            else if (*format == 's')
                ft_putstr(va_arg(list, char *), &counter);
        }
        else
            ft_putchar(*format, &counter);
        format++;
    }
    va_end(list);
    return (counter);
}
