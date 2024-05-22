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

bvar::LatencyRecorder g_latency_recorder("client");
bvar::Adder<int> g_error_count("client_error_count");
void Benchmark_Report(benchmark::State &state)
{
    while (state.KeepRunning())
    {
        g_error_count << 1;
    }
}

BENCHMARK(Benchmark_Report)->Iterations(10000);
BENCHMARK(Benchmark_Report);

BENCHMARK_MAIN();
