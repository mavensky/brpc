// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.

// A client sending requests to server by multiple threads.

#include <bvar/bvar.h>
#include <benchmark/benchmark.h>
#include <thread>
#include "bvar/multi_dimension.h"
#include <list>

bvar::LatencyRecorder g_latency_recorder("client");
bvar::Adder<int> g_error_count("client_error_count");
static const std::list<std::string> labels = {"idc", "method", "status"};

void Benchmark_BVar(benchmark::State &state)
{
    while (state.KeepRunning())
    {
        g_error_count << 1;
    }
}

void Benchmark_MVar(benchmark::State &state)
{
    std::list<std::string> labels_value = {"bj", "get", "200"};
    bvar::MultiDimension<bvar::Adder<uint32_t>> my_madder1("request_count_madder_uint32_t", labels);
    while (state.KeepRunning())
    {
        bvar::Adder<uint32_t> *my_adder1 = my_madder1.get_stats(labels_value);
        *my_adder1 << 2;
    }
}
BENCHMARK(Benchmark_BVar)->Iterations(10000);
BENCHMARK(Benchmark_BVar);

BENCHMARK(Benchmark_MVar)->Iterations(10000);
BENCHMARK(Benchmark_MVar);

BENCHMARK_MAIN();
