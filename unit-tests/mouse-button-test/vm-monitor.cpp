#include "vm-monitor.hpp"

#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>

#include <iostream>
using namespace std;

void watch_vm_dir(bool* stop_vm_monitor, VmStates* vm_states)
{
    // fd = inotify_init();
    int fd = inotify_init1(IN_NONBLOCK);
    if (fd == -1)
    {
        throw std::runtime_error("inotify_init1() failed");
    }

    int wd = inotify_add_watch(fd, "/var/run/libvirt/qemu", IN_CREATE | IN_DELETE);

    if (wd == -1)
    {
        throw std::runtime_error(strerror(errno));
    }

    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;

    while (*stop_vm_monitor == false)
    {
        // poll_num = poll(fds, nfds, -1);
        int poll_num = poll(fds, 1, 300); // Block for 300ms to save cpu time? ok
        if (poll_num == -1)
        {
            if (errno == EINTR) continue;

            throw std::runtime_error("poll() failed");
        }

        if (poll_num > 0)
        {
            if (fds[0].revents & POLLIN)
            {
                /* Inotify events are available. */
                // handle_events(fd, wd);

                char buf[4096]
                    __attribute__ ((aligned(__alignof__(struct inotify_event))));

                const struct inotify_event *event;

                ssize_t len = read(fd, buf, sizeof(buf));
                if (len == -1 && errno != EAGAIN)
                {
                    throw std::runtime_error("read() failed");
                }

                /* Loop over all events in the buffer. */
                for (char *ptr = buf; ptr < buf + len;
                        ptr += sizeof(struct inotify_event) + event->len)
                {
                    event = (const struct inotify_event *) ptr;

                    if (strcmp(event->name, "GoldLinux.pid") == 0)
                    {
                        if (event->mask & IN_CREATE) vm_states->GoldLinux_is_running = true;
                        if (event->mask & IN_DELETE) vm_states->GoldLinux_is_running = false;
                    }
                    if (strcmp(event->name, "GoldWin10.pid") == 0)
                    {
                        if (event->mask & IN_CREATE) vm_states->GoldWin10_is_running = true;
                        if (event->mask & IN_DELETE) vm_states->GoldWin10_is_running = false;
                    }
                    if (strcmp(event->name, "SilverWin.pid") == 0)
                    {
                        if (event->mask & IN_CREATE) vm_states->SilverWin_is_running = true;
                        if (event->mask & IN_DELETE) vm_states->SilverWin_is_running = false;
                    }
                }
            }
        }
    }

    //printf("Listening for events stopped.\n");

    close(fd);
}
