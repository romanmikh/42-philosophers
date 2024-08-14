#include "philo.h"

// Checks if the long long value is within valid limits
int	validate_long_long(int sign, t_msec *n)
{
	if (!sign && *n == LLONG_MIN)
		return (2);
	if (*n < 0 && *n != LLONG_MIN)
		return (2);
	return (0);
}

// Converts a string to a long long integer and validates the result
int	convert_str_to_long_long(const char *str, t_msec *n)
{
	int	sign;

	sign = 0;
	*n = 0;
	if (*str == '+')
		str++;
	if (*str < '0' && *str > '9')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		*n *= 10;
		*n += *str - '0';
		if (validate_long_long(sign, n))
			return (2);
		str++;
	}
	if (*str == '\0')
		return (0);
	return (1);
}

// Checks if the integer value is within valid limits
int	validate_int(int sign, int *n)
{
	if (!sign && *n == INT_MIN)
		return (2);
	if (*n < 0 && *n != INT_MIN)
		return (2);
	return (0);
}

// Converts a string to an integer and validates the result
int	convert_str_to_int(const char *str, int *n)
{
	int	sign;

	sign = 0;
	*n = 0;
	if (*str == '-')
		sign = 1;
	if (*str == '-' || *str == '+')
		str++;
	if (*str < '0' && *str > '9')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		*n *= 10;
		*n += *str - '0';
		if (validate_int(sign, n))
			return (2);
		str++;
	}
	if (sign)
		*n *= -1;
	if (*str == '\0')
		return (0);
	return (1);
}
