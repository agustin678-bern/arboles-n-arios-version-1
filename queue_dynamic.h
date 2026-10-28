typedef struct _ntree ntree;

#define QUEUE_ELEM ntree*
#define QUEUE_ELEM_DEFAULT NULL
typedef struct _queue queue;

queue* queue_new ();

queue* queue_new_with (int maxsize);

void queue_free (queue* q);

int queue_getsize (queue* q);

int queue_getmaxsize (queue* q);

int queue_isfull (queue* q);

int queue_isempty (queue* q);

void enqueue (queue* q, QUEUE_ELEM elem);

QUEUE_ELEM dequeue (queue* q);

QUEUE_ELEM peek (queue* q);
