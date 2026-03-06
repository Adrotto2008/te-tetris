#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <linux/joystick.h>

int main() {

    int fd = open("/dev/input/js0", O_RDONLY | O_NONBLOCK);

    if (fd < 0) {
        std::cout << "Errore apertura controller\n";
        return 1;
    }

    js_event e;

    int buttonCount[64] = {0};

    while (true) {

        while (read(fd, &e, sizeof(e)) > 0) {

            // Conta solo pressioni reali
            if (e.type == JS_EVENT_BUTTON && e.value == 1) {

                if (e.number < 64)
                    buttonCount[e.number]++;
            }
        }

        std::cout << "\033[2J\033[H";

        for (int i = 0; i < 16; i++) {
            std::cout << "Button " << i
                      << " = "
                      << buttonCount[i]
                      << "\n";
        }

        usleep(16000);
    }

    close(fd);
}