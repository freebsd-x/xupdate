#include "xserver/update_service.h"
#include "shared/protocol.h"
#include "shared/logger.h"
#include "xserver/crash_handler.h"
#include <csignal>
#include <unistd.h>
#include <atomic>

static std::atomic<bool> g_running{true};

static void signal_handler(int) {
    g_running = false;
}

int main() {
    fbx::shared::Logger::init("xupdate");
    fbx::xserver::installCrashHandler("xupdate");
    LOG_INFO("xupdate starting...");

    signal(SIGTERM, signal_handler);
    signal(SIGINT, signal_handler);

    LOG_INFO("UpdateService running. Waiting for SIGTERM/SIGINT.");

    // UpdateService handles OTA update checks and ZFS Boot Environment
    // upgrades via XBus. The IPC socket is managed by the compositor;
    // this daemon is a placeholder for standalone operation in the future.
    while (g_running) {
        pause();
    }

    LOG_INFO("xupdate shutting down.");
    return 0;
}
