#include <cstring>
#include <ctime>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100
#define SENDER_TYPE 1
#define RECEIVER_TYPE 2

struct Message {
    long mtype;
    char mtext[MAX_MESSAGE_SIZE];
};

int main() {
    key_t key = ftok("chat_app", 65); // Unique key for message queue

    // Prompt the user to enter their name
    std::string receiverName;
    std::cout << "Enter your name: ";
    std::cin >> receiverName;

    // Create the message queue for receiving messages
    int receivingQueueId = msgget(key, IPC_CREAT | 0666);
    if (receivingQueueId == -1) {
        std::cerr << "Failed to create receiving message queue." << std::endl;
        return 1;
    }

    std::cout << "Receiver ready. Waiting for messages..." << std::endl;

    while (true) {
        // Receive the message
        Message msg;
        if (msgrcv(receivingQueueId, &msg, sizeof(msg.mtext), RECEIVER_TYPE, 0) == -1) {
            std::cerr << "Failed to receive the message." << std::endl;
            continue;
        }

        // Get the current time
        std::time_t currentTime = std::time(nullptr);
        std::string timeStr = std::asctime(std::localtime(&currentTime));
        timeStr.pop_back(); // Remove the trailing newline character

        // Display the received message
        std::cout << timeStr << " - " << msg.mtext << std::endl;
    }

    return 0;
}
