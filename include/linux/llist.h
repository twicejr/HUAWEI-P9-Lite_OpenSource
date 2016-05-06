#ifndef LLIST_H
#define LLIST_H


#include <linux/kernel.h>
#include <asm/cmpxchg.h>

struct llist_head {
	struct llist_node *first;
};

struct llist_node {
	struct llist_node *next;
};

#define LLIST_HEAD_INIT(name)	{ NULL }
#define LLIST_HEAD(name)	struct llist_head name = LLIST_HEAD_INIT(name)

/**
 * init_llist_head - initialize lock-less list head
 * @head:	the head for your lock-less list
 */
static inline void init_llist_head(struct llist_head *list)
{
	list->first = NULL;
}

/**
 * llist_entry - get the struct of this entry
 * @ptr:	the &struct llist_node pointer.
 * @type:	the type of the struct this is embedded in.
 * @member:	the name of the llist_node within the struct.
 */
#define llist_entry(ptr, type, member)		\
	container_of(ptr, type, member)


#define llist_for_each(pos, node)			\
	for ((pos) = (node); pos; (pos) = (pos)->next)


#define llist_for_each_entry(pos, node, member)				\
	for ((pos) = llist_entry((node), typeof(*(pos)), member);	\
	     &(pos)->member != NULL;					\
	     (pos) = llist_entry((pos)->member.next, typeof(*(pos)), member))

/**
 * llist_empty - tests whether a lock-less list is empty
 * @head:	the list to test
 *
 * Not guaranteed to be accurate or up to date.  Just a quick way to
 * test whether the list is empty without deleting something from the
 * list.
 */
static inline bool llist_empty(const struct llist_head *head)
{
	return ACCESS_ONCE(head->first) == NULL;
}

static inline struct llist_node *llist_next(struct llist_node *node)
{
	return node->next;
}

/**
 * llist_add - add a new entry
 * @new:	new entry to be added
 * @head:	the head for your lock-less list
 *
 * Returns true if the list was empty prior to adding this entry.
 */
static inline bool llist_add(struct llist_node *new, struct llist_head *head)
{
	struct llist_node *entry, *old_entry;

	entry = head->first;
	for (;;) {
		old_entry = entry;
		new->next = entry;
		entry = cmpxchg(&head->first, old_entry, new);
		if (entry == old_entry)
			break;
	}

	return old_entry == NULL;
}

/**
 * llist_del_all - delete all entries from lock-less list
 * @head:	the head of lock-less list to delete all entries
 *
 * If list is empty, return NULL, otherwise, delete all entries and
 * return the pointer to the first entry.  The order of entries
 * deleted is from the newest to the oldest added one.
 */
static inline struct llist_node *llist_del_all(struct llist_head *head)
{
	return xchg(&head->first, NULL);
}

extern bool llist_add_batch(struct llist_node *new_first,
			    struct llist_node *new_last,
			    struct llist_head *head);
extern struct llist_node *llist_del_first(struct llist_head *head);

#endif /* LLIST_H */
