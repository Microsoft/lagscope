// ----------------------------------------------------------------------------------
// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.
// Author: Shihua (Simon) Xiao, sixiao@microsoft.com
// ----------------------------------------------------------------------------------

#ifndef UTIL_H
#define UTIL_H

#include "common.h"
#include "lagscope.h"
#include "const.h"

void print_flags(struct lagscope_test *test);
void print_usage();
void print_version();
int verify_args(struct lagscope_test *test);
int parse_arguments(struct lagscope_test *test, int argc, char **argv);

void print_iteration_histogram();
void print_test_stats();

int process_latencies(unsigned long max_latency);
int show_percentile(unsigned long, unsigned long);
int show_histogram(int, int, int, unsigned long);
void create_latencies_csv(const char *);
void create_freq_table_json(unsigned long, const char *);
void push(unsigned long);
void latencies_stats_cleanup(void);

char *retrive_ip_address_str(struct sockaddr_storage *ss, char *ip_str, size_t maxlen);

long long time_in_nanosec(void);
int set_affinity(int cpuid);
void run_test_timer(int duration);

static inline void report_progress(struct lagscope_test_runtime *test_runtime)
{
	/*
	 * Only report progress once in every lazy_prog_report_factor of pings
	 * (try to increase ~1%, by estimation)
	 */
	if (test_runtime->ping_elapsed % test_runtime->lazy_prog_report_factor != 0)
		return;

	if (test_runtime->test->test_mode == PING_ITERATION) {
		printf("%s: %lu%% completed.\r",
		test_runtime->test->bind_address,
		test_runtime->ping_elapsed * 100 / test_runtime->test->iteration);
	}
	else {
		long long time_elapsed = test_runtime->current_time - test_runtime->start_time;
		printf("%s: %lld%% completed.\r",
		test_runtime->test->bind_address,
		time_elapsed / 10000000 / test_runtime->test->duration);
	}
	fflush(stdout);
}

#endif // UTIL_H
