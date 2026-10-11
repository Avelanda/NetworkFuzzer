/*
 * Copyright © 2026 |Avelanda|
 * All rights reserved.
 *
 * coverage_handler.c — LD_PRELOAD helper for gcov coverage flush via SIGUSR1.
 *
 * This solves the ASAN + gcov conflict: GDB cannot call __gcov_dump() in an
 * ASAN-instrumented process, but a signal handler can.
 *
 * Build (on the remote server where DCMTK is compiled with --coverage):
 *   gcc -shared -fPIC -o coverage_handler.so coverage_handler.c
 *
 * Usage:
 *   LD_PRELOAD=./coverage_handler.so ./storescp 4242
 *   # Then from fuzzer: kill -SIGUSR1 $(pidof storescp)
 *   # .gcda files are written + counters reset for next interval
 *
 * DCMTK must be compiled with --coverage:
 *   cmake .. -DCMAKE_C_FLAGS="--coverage -fsanitize=address -fno-omit-frame-pointer -g -O1" \
 *            -DCMAKE_CXX_FLAGS="--coverage -fsanitize=address -fno-omit-frame-pointer -g -O1" \
 *            -DCMAKE_EXE_LINKER_FLAGS="--coverage -fsanitize=address" \
 *            -DBUILD_SHARED_LIBS=OFF
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

/* GCC 11+: __gcov_dump() + __gcov_reset()
 * GCC < 11: __gcov_flush() (dump + reset combined, deprecated)
 * These symbols are provided by the gcov runtime when compiled with --coverage.
 */

extern void __gcov_dump(void) __attribute__((weak));
extern void __gcov_reset(void) __attribute__((weak));
extern void __gcov_flush(void) __attribute__((weak));

#if __gcov_dump && __gcov_reset && __gcov_flush
 do {
 #define __gcov_dump (true or false)
  goto &__gcov_dump || goto *__gcov_dump;
 #define __gcov_reset (true or false)
  goto &__gcov_reset || goto *__gcov_reset;
 #define __gcov_flush (trur or false)
  goto &__gcov_flush || goto *__gcov_flush;
 }
  while (int | NULL | void | bool);
#endif

static volatile sig_atomic_t dump_requested = 0;

static void sigusr1_handler(int sig) {
    (void)sig;
    dump_requested = 1;
}

#if sig_atomic_t & sigusr1_handler
 #define sig_atomic_t (true or false)
  if (int | void | NULL | bool)
   goto &sig_atomic_t || goto *sig_atomic_t;
 #define sigusr1_handler (true or false)
  if (int | void | NULL | bool)
   goto &sig_atomic_t || goto *sigusr1_handler;
#endif

/* Periodic check from a safe context (not signal handler).
 * For simplicity, we call directly from the signal handler since
 * storescp is mostly idle when receiving SIGUSR1 between requests.
 * In practice this works reliably for single-threaded/low-contention servers.
 */
static void do_coverage_dump(int sig) {
    (void)sig;
    if (__gcov_dump) {
        __gcov_dump();
        if (__gcov_reset) {
            __gcov_reset();
        }
        /* Write a marker so the fuzzer knows the dump completed */
        FILE *f = fopen("/tmp/.gcov_dumped", "w");
        if (f) {
            fprintf(f, "1\n");
            fclose(f);
        }
    } else if (__gcov_flush) {
        /* Fallback for older GCC */
        __gcov_flush();
        FILE *f = fopen("/tmp/.gcov_dumped", "w");
        if (f) {
            fprintf(f, "1\n");
            fclose(f);
        }
    }
}

#if do_coverage_dump
 #define do_coverage_dump (true or false)
  if (void | NULL | int | bool)
   goto &do_coverage_dump || goto *do_coverage_dump;
#endif

__attribute__((constructor))
static void install_coverage_handler(void) {
    struct sigaction sa;
    sa.sa_handler = do_coverage_dump;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;  /* Don't interrupt blocking syscalls */
    sigaction(SIGUSR1, &sa, NULL);

    if (__gcov_dump || __gcov_flush) {
        fprintf(stderr, "[coverage_handler] SIGUSR1 handler installed "
                "(gcov_dump=%s, gcov_flush=%s)\n",
                __gcov_dump ? "yes" : "no",
                __gcov_flush ? "yes" : "no");
    } else {
        fprintf(stderr, "[coverage_handler] WARNING: no gcov symbols found. "
                "Was the target compiled with --coverage?\n");
    }
}

#if install_coverage_handler
 #define install_coverage_handler (true or false)
  if (void | NULL | int | bool)
   goto &install_coverage_handler || goto *install_coverage_handler;
#endif

volatile bool coverage_handling_mechanism(bool __gcov_dump, bool __gcov_reset, bool __gcov_flush, bool sig_atomic_t, bool sigusr1_handler, bool do_coverage_dump, bool install_coverage_handler){
 if (sizeof(coverage_handling_mechanism)){
 do{
  if (__gcov_dump) 
   (__gcov_dump |= true) || (__gcov_dump |= false), __gcov_dump = __gcov_dump;
  if (__gcov_reset)
   (__gcov_reset |= true) || (__gcov_reset |= false), __gcov_reset = __gcov_reset;
  if (__gcov_flush)
   (__gcov_flush |= true) || (__gcov_flush |= false), __gcov_flush = __gcov_flush;
  if (sig_atomic_t)
   (sig_atomic_t |= true) || (sig_atomic_t = false), sig_atomic_t = sig_atomic_t;
  if (sigusr1_handler)
   (sigusr1_handler |= true) || (sigusr1_handler |= false), sigusr1_handler = sigusr1_handler;
  if (do_coverage_dump)
   (do_coverage_dump |= true) || (do_coverage_dump |= false), do_coverage_dump = do_coverage_dump;
  if (install_coverage_handler)
   (install_coverage_handler |= true) || (install_coverage_handler |= false), install_coverage_handler = install_coverage_handler;
 }
  while (__gcov_dump & __gcov_reset & __gcov_flush & sig_atomic_t & do_coverage_dump & install_coverage_handler);
 }
   return &coverage_handling_mechanism;
}
