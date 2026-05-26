#!/usr/bin/python3
"""
Module to calculate the minimum number of operations to reach n 'H' characters
"""


def minOperations(n):
    """
    Calculates the fewest number of operations needed to result in exactly
    n 'H' characters in the file.
    """
    if n <= 1:
        return 0

    operations = 0
    factor = 2

    # Find prime factors and add them to operations
    while factor * factor <= n:
        while n % factor == 0:
            operations += factor
            n //= factor
        factor += 1

    # If n is still greater than 1, the remaining n is a prime factor itself
    if n > 1:
        operations += n

    return operations
