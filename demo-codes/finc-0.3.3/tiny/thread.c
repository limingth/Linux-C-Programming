#include <stdio.h>

#include <tiny/thread.h>

#ifdef HAVE_THREAD

#include <errno.h>
#include <pthread.h>

Thread* thread_new(ThreadFunc func, ADT data, Bool joinable, Bool bound)
{
	Thread* self;
	pthread_attr_t attr;

	self = (Thread*) mem_new (sizeof(Thread));
	self->data = data;
	self->thread = (pthread_t*)mem_new(sizeof(pthread_t));

	self->func = func;
	self->joinable = joinable;
	object_init_object((Object*)self, thread_destroy);

	pthread_attr_init (&attr);
	if (bound) pthread_attr_setscope (&attr, PTHREAD_SCOPE_SYSTEM);
	pthread_attr_setdetachstate (&attr, joinable ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED);

	pthread_create ((pthread_t*)self->thread, &attr, (void* (*)(void*))self->func, self->data);

	pthread_attr_destroy (&attr);

	if (joinable)pthread_detach(*(pthread_t*)self->thread);

	return self;
}

void thread_destroy(Object* self)
{
	mem_destroy(((Thread*)self)->thread);
	mem_destroy(self);
}

void thread_cancel(Thread* other)
{
	if (!other)return;

	pthread_cancel(*(pthread_t*)other->thread);
}

void thread_join(Thread* other)
{
	ADT ignore;

	pthread_join (*(pthread_t*)other->thread, &ignore);
}

void thread_self(Thread* self)
{
	if (!self) return;
	*(pthread_t*)self->thread = pthread_self();
}

void thread_testcancel()
{
	pthread_testcancel();
}

void thread_exit()
{
	pthread_exit(NULL);
}

Mutex* mutex_new()
{
	Mutex* self;

	self = (Mutex*)mem_new(sizeof(Mutex));
	self->mutex = mem_new(sizeof(pthread_mutex_t));
	pthread_mutex_init ((pthread_mutex_t *)self->mutex, NULL);

	object_init_object((Object*)self, mutex_destroy);

	return self;
}

void mutex_destroy(Object* self)
{
	pthread_mutex_destroy ((pthread_mutex_t *) ((Mutex*)self)->mutex);
	mem_destroy(((Mutex*)self)->mutex);
	mem_destroy(self);
}

void mutex_lock(Mutex* self)
{
	pthread_mutex_lock((pthread_mutex_t *) self->mutex);
}

void mutex_unlock(Mutex* self)
{
	pthread_mutex_unlock((pthread_mutex_t *) self->mutex);
}

Bool mutex_try_lock(Mutex* self)
{
	int result;

	result = pthread_mutex_trylock ((pthread_mutex_t *) self->mutex);

	if (result == EBUSY)return FALSE;

	return TRUE;
}

Cond* cond_new()
{
	Cond* self;

	self = (Cond*)mem_new(sizeof(Cond));
	self->cond = mem_new(sizeof(pthread_cond_t));
	pthread_cond_init ((pthread_cond_t *) self->cond, NULL);

	object_init_object((Object*)self, cond_destroy);

	return self;
}

void  cond_destroy(Object* self)
{
	pthread_cond_destroy ((pthread_cond_t *) ((Cond*)self)->cond);
	mem_destroy((pthread_cond_t *) ((Cond*)self)->cond);
	mem_destroy(self);
}

void  cond_signal(Cond* self)
{
	pthread_cond_signal((pthread_cond_t*)self->cond);
}

void  cond_wait(Cond* self, Mutex* mutex)
{
	pthread_cond_wait((pthread_cond_t*)self->cond, (pthread_mutex_t*)mutex->mutex);
}

Bool  cond_timewait(Cond* self, Mutex* mutex)
{
/*
	int result;
	struct timespec end_time;
	Bool timed_out;

	if (!self)return FALSE;
	if (!mutex)return FALSE;

	if (!abs_time)
	{
		g_cond_wait (cond, mutex);
		return TRUE;
	}

	end_time.tv_sec = abs_time->tv_sec;
	end_time.tv_nsec = abs_time->tv_usec * (G_NSEC_PER_SEC / G_USEC_PER_SEC);

	if (end_time.tv_nsec < G_NSEC_PER_SEC) return TRUE;

	result = pthread_cond_timedwait ((pthread_cond_t *) cond->cond, 
			(pthread_mutex_t *) mutex->mutex,
			&end_time);

	timed_out = (result == ETIMEDOUT);

	return !timed_out;
*/
	return TRUE;
}

void  cond_broadcast(Cond* self)
{
	pthread_cond_broadcast((pthread_cond_t*)self->cond);
}

#endif
