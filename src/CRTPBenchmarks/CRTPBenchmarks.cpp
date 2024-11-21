#include <benchmark/benchmark.h>
#include <vector>
#include <iostream>
#include <memory>

// Polymorphism with virtual functions
struct BaseVirtual {
    virtual ~BaseVirtual() = default;
    virtual void Update() = 0;
};

struct DerivedVirtual : BaseVirtual {
    void Update() override {
        volatile int x = 0; // Prevent optimization
        x++;
    }
};

// CRTP Implementation
template <typename Derived>
struct BaseCRTP {
    void Update() {
        static_cast<Derived*>(this)->Update();
    }
};

struct DerivedCRTP : BaseCRTP<DerivedCRTP> {
    void Update() {
        volatile int x = 0; // Prevent optimization
        x++;
    }
};

// Benchmark for virtual functions
static void BM_VirtualFunctions(benchmark::State& state) {
    std::vector<std::unique_ptr<BaseVirtual> > objects;
    for (size_t i = 0; i < state.range(0); ++i) {
        objects.push_back(std::make_unique<DerivedVirtual>());
    }
    for (auto _ : state) {
        for (auto& obj : objects) {
            obj->Update();
        }
    }
}
BENCHMARK(BM_VirtualFunctions)->Range(8, 8 << 10);

// Benchmark for CRTP
static void BM_CRTP(benchmark::State& state) {
    std::vector<DerivedCRTP> objects(state.range(0));
    for (auto _ : state) {
        for (auto& obj : objects) {
            obj.Update();
        }
    }
}
BENCHMARK(BM_CRTP)->Range(8, 8 << 10);

BENCHMARK_MAIN();
