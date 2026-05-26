#!/usr/bin/python3
"""
Module for lockboxes problem
"""


def canUnlockAll(boxes):
    """
    Determines if all locked boxes can be opened.

    Args:
        boxes (list of lists): Each index is a box containing keys

    Returns:
        bool: True if all boxes can be opened, False otherwise
    """
    n = len(boxes)
    visited = set([0])
    keys = list(boxes[0])

    while keys:
        key = keys.pop()
        if key < n and key not in visited:
            visited.add(key)
            keys.extend(boxes[key])

    return len(visited) == n
