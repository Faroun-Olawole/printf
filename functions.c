#include "main.h"

/**
 * print_char - a char is printed
 * @types: arguments are listed
 * @buffer: print is handle by Buffer array
 * @flags:  active flags is calculated
 * @width:  the width
 * @precision: specification precision
 * @size: specifier size
 * Return: chars number printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/**
 * print_string - a string is printed
 * @types: arguments list
 * @buffer:print is handle by Buffer array
 * @flags:  active flags is calculated
 * @width:  the width
 * @precision: specification precision
 * @size: specifier size
 * Return: chars number printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, j;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**
 * print_percent - Prints a percent sign
 * @types: arguments list
 * @buffer:print is handle by Buffer array
 * @flags:  active flags is calculated
 * @width:  the width
 * @precision: specification precision
 * @size: specifier size
 * Return: chars number printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}


/**
 * print_int - Print int
 * @types: arguments list
 * @buffer:print is handle by Buffer array
 * @flags:  active flags is calculated
 * @width:  the width
 * @precision: specification precision
 * @size: specifier size
 * Return: chars number printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_number(is_negative, j, buffer, flags, width, precision, size));
}

/**
 * print_binary - Prints an unsigned number
 * @types: arguments list
 * @buffer:print is handle by Buffer array
 * @flags:  active flags is calculated
 * @width:  the width
 * @precision: specification precision
 * @size: specifier size
 * Return: chars number printed
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int z, u, j, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	z = va_arg(types, unsigned int);
	u = 2147483648; /* (2 ^ 31) */
	a[0] = z / u;
	for (j = 1; j < 32; j++)
	{
		u /= 2;
		a[j] = (z / u) % 2;
	}
	for (j = 0, sum = 0, count = 0; j < 32; j++)
	{
		sum += a[j];
		if (sum || j == 31)
		{
			char y = '0' + a[j];

			write(1, &y, 1);
			count++;
		}
	}
	return (count);
}

