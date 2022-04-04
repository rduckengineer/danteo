#ifndef DANTEO_FAKE_INTERACTIVE_SCREEN_HPP
#define DANTEO_FAKE_INTERACTIVE_SCREEN_HPP

#include "ftxui/component/task.hpp"
#include "ftxui/component/component.hpp"

#include <atomic>
#include <mutex>

struct FakeInteractiveScreen {
    void Post(ftxui::Task task) {
        std::scoped_lock l{pendingTaskMutex_};
        pendingTask_ = std::move(task);
    }

    void Loop(ftxui::Component component) { // NOLINT API takes by copy
        running = true;
        while (running) {
            {
                std::scoped_lock l{pendingTaskMutex_};
                if (pendingTask_) {
                    std::get<ftxui::Closure>(pendingTask_.value())();
                    pendingTask_.reset();
                }
            }
            loopMock_(component);
        }
    }
    void RequestAnimationFrame() { requestAnimMock_(); }

    void mockLoop(std::function<void(ftxui::Component)> loopMock) {
        loopMock_ = std::move(loopMock);
    }

    void mockRequestAnimation(std::function<void()> requestAnimationMock) {
        requestAnimMock_ = std::move(requestAnimationMock);
    }

    void stopRunning() { running = false; }

private:
    std::atomic<bool>                            running = false;
    std::function<void(ftxui::Component const&)> loopMock_{};
    std::function<void()>                        requestAnimMock_{};
    std::optional<ftxui::Task>                   pendingTask_ = std::nullopt;
    std::mutex                                   pendingTaskMutex_{};
};

#endif // DANTEO_FAKE_INTERACTIVE_SCREEN_HPP
