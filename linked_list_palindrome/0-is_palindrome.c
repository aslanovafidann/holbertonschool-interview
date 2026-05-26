#include <stdio.h>
#include <stdlib.h>
#include "lists.h"

/**
 * reverse_list - Reverses a singly linked list.
 * @head: Pointer to the head node of the list to reverse.
 *
 * Return: A pointer to the new head of the reversed list.
 */
listint_t *reverse_list(listint_t *head)
{
	listint_t *prev = NULL;
	listint_t *current = head;
	listint_t *next = NULL;

	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	return (prev);
}

/**
 * is_palindrome - Checks if a singly linked list is a palindrome.
 * @head: Double pointer to the head of the linked list.
 *
 * Return: 0 if it is not a palindrome, 1 if it is a palindrome.
 */
int is_palindrome(listint_t **head)
{
	listint_t *slow = *head;
	listint_t *fast = *head;
	listint_t *second_half = NULL;
	listint_t *p1 = *head;
	listint_t *p2 = NULL;
	int palindrome = 1;

	/* An empty list or a list with a single node is a palindrome */
	if (*head == NULL || (*head)->next == NULL)
		return (1);

	/* Step 1: Find the middle node using tortoise and hare */
	while (fast != NULL && fast->next != NULL)
	{
		slow = slow->next;
		fast = fast->next->next;
	}

	/* Step 2: Reverse the second half of the linked list */
	second_half = reverse_list(slow);
	p2 = second_half;

	/* Step 3: Compare values between first half and reversed second half */
	while (p2 != NULL)
	{
		if (p1->n != p2->n)
		{
			palindrome = 0;
			break;
		}
		p1 = p1->next;
		p2 = p2->next;
	}

	/* Step 4: Restore the original list structure before returning */
	reverse_list(second_half);

	return (palindrome);
}
