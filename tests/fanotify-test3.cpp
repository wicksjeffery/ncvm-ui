
#include <errno.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>


void handle_events(int fd, int wd)
{

//     /* Some systems cannot read integer variables if they are not
//         properly aligned. On other systems, incorrect alignment may
//         decrease performance. Hence, the buffer used for reading from
//         the inotify file descriptor should have the same alignment as
//         struct inotify_event. */
//
    printf("Pooped.\n");
    char buf[4096]
        __attribute__ ((aligned(__alignof__(struct inotify_event))));
    const struct inotify_event *event;
    ssize_t len;

    /* Loop while events can be read from inotify file descriptor. */


    // for (;;) {

        /* Read some events. */

        len = read(fd, buf, sizeof(buf));
        if (len == -1 && errno != EAGAIN) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        /* If the nonblocking read() found no events to read, then
            it returns -1 with errno set to EAGAIN. In that case,
            we exit the loop. */

        printf("Hey: %d\n", len);

        if (len <= 0)
            return;

        /* Loop over all events in the buffer. */

        for (char *ptr = buf; ptr < buf + len;
                ptr += sizeof(struct inotify_event) + event->len) {

            event = (const struct inotify_event *) ptr;

            /* Print event type. */

            if (event->mask & IN_CREATE)
                printf("IN_CREATE: ");
            if (event->mask & IN_DELETE)
                printf("IN_DELETE: ");

                if (wd == event->wd) {
                    printf("%s/\n", "/tmp");
                    // break;
                }


            /* Print the name of the file. */

            if (event->len)
                printf("%s", event->name);

            /* Print type of filesystem object. */

            if (event->mask & IN_ISDIR)
                printf(" [directory]\n");
            else
                printf(" [file]\n");
        }
}



int main()
{
    char buf;
    int fd, i, poll_num;
    int wd;
    nfds_t nfds;
    struct pollfd fds[1];

    fd = inotify_init();
    if (fd == -1) {
        perror("inotify_init1");
        exit(EXIT_FAILURE);
    }

    // for (i = 1; i < argc; i++) {
        wd = inotify_add_watch(fd, "/tmp", IN_CREATE | IN_DELETE);
        // wd = inotify_add_watch(fd, "/tmp", IN_ALL_EVENTS);
        if (wd == -1)
        {
            fprintf(stderr, "Cannot watch /tmp: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

    fds[0].fd = fd;                 /* Inotify input */
    fds[0].events = POLLIN;

    printf("Listening for events.\n");
    while (1)
    {
        // poll_num = poll(fds, nfds, -1);
        poll_num = poll(fds, 1, -1);
        if (poll_num == -1) {
            if (errno == EINTR)
                continue;
            perror("poll");
            exit(EXIT_FAILURE);
        }

        if (poll_num > 0)
        {
            if (fds[0].revents & POLLIN)
            {
                /* Inotify events are available. */
                handle_events(fd, wd);
            }
        }
    }

    printf("Listening for events stopped.\n");
    //
    // /* Close inotify file descriptor. */
    //
    // close(fd);
    //
    // free(wd);
    // exit(EXIT_SUCCESS);
}
