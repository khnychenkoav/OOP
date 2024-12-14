#ifndef CUSTOM_GENERATOR_H
#define CUSTOM_GENERATOR_H

#include <coroutine>
#include <exception>
#include <optional>
#include <variant>
#include <iostream>

template <typename T = std::monostate>
class Generator {
public:
    struct promise_type {
        std::optional<T> current_value;

        promise_type() = default;
        ~promise_type() = default;

        auto get_return_object() {
            return Generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        auto initial_suspend() const noexcept {
            return std::suspend_always{};
        }

        auto final_suspend() const noexcept {
            return std::suspend_always{};
        }

        auto yield_value(T value) noexcept {
            current_value = value;
            return std::suspend_always{};
        }

        void return_void() noexcept {}
        void unhandled_exception() { std::terminate(); }
    };

    explicit Generator(std::coroutine_handle<promise_type> coroutine) : coroutine(coroutine) {}
    ~Generator() {
        if (coroutine) coroutine.destroy();
    }

    Generator(const Generator&) = delete;
    Generator& operator=(const Generator&) = delete;

    Generator(Generator&& other) noexcept : coroutine(other.coroutine) {
        other.coroutine = nullptr;
    }

    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (coroutine) coroutine.destroy();
            coroutine = other.coroutine;
            other.coroutine = nullptr;
        }
        return *this;
    }

    std::optional<T> next() {
        coroutine.resume();
        return coroutine.promise().current_value;
    }

    bool done() const {
        return !coroutine || coroutine.done();
    }

private:
    std::coroutine_handle<promise_type> coroutine;
};

#endif // CUSTOM_GENERATOR_H
