#pragma once

#define DEBUG 1

extern void *__libc_malloc(size_t size);
extern void __libc_free(void *ptr);

int malloc_hook_active = 1;
int free_hook_active = 1;

void* malloc_hook(size_t size, void *caller)
{
	void *result;

	// deactivate hooks for logging
	malloc_hook_active = 0;

	result = malloc(size);

	// do logging
	printf("[+] malloc (%u) returns %p, caller: %p\n", (unsigned int) size, result, caller);

	// reactivate hooks
	malloc_hook_active = 1;

	return result;
}

void free_hook(void *ptr, void *caller)
{
	// deactivate hooks for logging
	free_hook_active = 0;

	free(ptr);

	// do logging
	printf("[+] free %p, caller: %p\n", ptr, caller);

	// reactivate hooks
	free_hook_active = 1;
}

void* malloc(size_t size)
{
	void *caller = __builtin_return_address(0);
	if (malloc_hook_active)
		return malloc_hook(size, caller);
	return __libc_malloc(size);
}

void free(void *ptr)
{
	void *caller = __builtin_return_address(0);
	if (free_hook_active)
		free_hook(ptr, caller);
	__libc_free(ptr);
}