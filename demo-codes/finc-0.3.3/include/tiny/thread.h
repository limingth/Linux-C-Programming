#ifndef _THREAD_H_
#define _THREAD_H_

#include <tiny/global.h>
#include <tiny/string.h>

/*if support thread.*/
#ifdef HAVE_THREAD

typedef void (*ThreadFunc) (ADT data);

typedef struct _Thread Thread;
typedef struct _Mutex Mutex;
typedef struct _Cond Cond;

struct _Thread
{
	Object parent;
	ADT thread;

	ADT data;
	ThreadFunc func;
	Bool joinable;
};

Thread* thread_new(ThreadFunc func, ADT data, Bool joinable, Bool bound);
void thread_destroy(Object* self);

void thread_cancel(Thread* other);
void thread_join(Thread* ohter);
void thread_self(Thread* other);
void thread_testcancel();
void thread_exit();

struct _Mutex
{
	Object parent;
	ADT* mutex;
};

Mutex* mutex_new();
void mutex_destroy(Object* self);
void mutex_lock(Mutex* self);
void mutex_unlock(Mutex* self);
Bool mutex_try_lock(Mutex* self);

#define lock(mutex)		mutex_lock(mutex)
#define unlock(mutex)	mutex_unlock(mutex)

struct _Cond
{
	Object parent;
	ADT* cond;
};

Cond* cond_new();
void  cond_destroy(Object* self);
void  cond_signal(Cond* self);
void  cond_wait(Cond* self, Mutex* mutex);
Bool  cond_timewait(Cond* self, Mutex* mutex);
void  cond_broadcast(Cond* self);

#endif

#endif
