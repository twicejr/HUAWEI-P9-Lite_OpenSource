#include <linux/spinlock.h>			/* For spin_lock/spin_unlock/... */

#define QUEUE_NAME_LEN 16

#define MOD_ADD(x, y, m)  (((x + y) > m) ? ((x + y) - m) : (x + y))
#define MOD_SUB(x, y, m)  ((x < y) ? (x + m - y) : (x - y))
#define MOD_INC(x, m)     (((x + 1) == m) ? 0 : (x + 1))


struct queue
{
    char name[QUEUE_NAME_LEN];
    spinlock_t lock;
    unsigned int max;
    unsigned int head; /*to write in index*/
    unsigned int tail; /*to read out index*/
    unsigned int in;   /*in times*/
    unsigned int out;  /*out times*/
    char data[4];
};



void queue_init(struct queue *q, char *name, unsigned int len);
void queue_destory(struct queue *q);
void _queue_loop_in(struct queue *q, void *element, unsigned int len);
void queue_loop_in(struct queue *q, void *element, unsigned int len);
int _queue_in(struct queue *q, void *element, unsigned int len);
int queue_in(struct queue *q, void *element, unsigned int len);
int _queue_out(struct queue *q, void *element, unsigned int len);
int queue_out(struct queue *q, void *element, unsigned int len);


