#!/usr/bin/python3
"""
Log parsing script that processes stdin line by line, computing metrics
and printing statistics every 10 lines or upon a KeyboardInterrupt.
"""
import sys


def print_stats(total_size, status_counts):
    """
    Helper function to print accumulated metrics in the required format.
    """
    print("File size: {}".format(total_size))
    # Print status codes in ascending order
    for code in sorted(status_counts.keys()):
        if status_counts[code] > 0:
            print("{}: {}".format(code, status_counts[code]))


def parse_logs():
    """
    Reads from standard input and processes line metrics dynamically.
    """
    total_size = 0
    line_count = 0

    # Dictionary initialized to track specific HTTP status code frequencies
    status_counts = {
        "200": 0, "301": 0, "400": 0, "401": 0,
        "403": 0, "404": 0, "405": 0, "500": 0
    }

    try:
        for line in sys.stdin:
            line_count += 1
            tokens = line.split()

            # Ensure there are enough tokens to read status and size
            if len(tokens) >= 2:
                # Extract file size and status code from the end
                file_size_str = tokens[-1]
                status_code_str = tokens[-2]

                # Accumulate file size metrics
                try:
                    total_size += int(file_size_str)
                except ValueError:
                    pass

                # Accumulate status code metrics
                if status_code_str in status_counts:
                    status_counts[status_code_str] += 1

            # Print statistics every 10 lines
            if line_count % 10 == 0:
                print_stats(total_size, status_counts)

        # Print final metrics if the stream completes cleanly
        print_stats(total_size, status_counts)

    except KeyboardInterrupt:
        # Handle Ctrl+C interruptions cleanly and re-raise
        print_stats(total_size, status_counts)
        raise


if __name__ == "__main__":
    parse_logs()
