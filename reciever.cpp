#include <cstring>
#include <ctime>
#include <iostream>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100
#define SENDER_TYPE 1
#define RECEIVER_TYPE 2

using namespace std;

struct Message {
    long mtype;
    char mtext[MAX_MESSAGE_SIZE];
};

int main() {
    key_t key = ftok("chat_app", 65); // Unique key for message queue

    // Prompt the user to enter their name
    string receiverName;
    cout << "Enter your name: ";
    cin >> receiverName;

    // Create the message queue for receiving messages
    int receivingQueueId = msgget(key, IPC_CREAT | 0666);
    if (receivingQueueId == -1) {
        cerr << "Failed to create receiving message queue." << endl;
        return 1;
    }

    cout << "Receiver ready. Waiting for messages..." << endl;

    while (true) {
        // Receive the message
        Message msg;
        if (msgrcv(receivingQueueId, &msg, sizeof(msg.mtext), RECEIVER_TYPE, 0) == -1) {
            cerr << "Failed to receive the message." << endl;
            continue;
        }

        // Get the current time
        time_t currentTime = time(nullptr);
        string timeStr = asctime(localtime(&currentTime));
        timeStr.pop_back(); // Remove the trailing newline character

        // Display the received message
        cout << timeStr << " - " << msg.mtext << endl;
    }

    return 0;
}
