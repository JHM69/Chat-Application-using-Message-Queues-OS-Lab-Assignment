#include <cstring>
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

    // Create the message queue for sending messages
    int sendingQueueId = msgget(key, IPC_CREAT | 0666);
    if (sendingQueueId == -1) {
        cerr << "Failed to create sending message queue." << endl;
        return 1;
    }

    // Prompt the user to enter their name
    string senderName;
    cout << "Enter your name: ";
    cin >> senderName;

    // Create the message queue for receiving messages
    int receivingQueueId = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (receivingQueueId == -1) {
        cerr << "Failed to create receiving message queue." << endl;
        return 1;
    }

    cout << "Sender ready. Enter 'quit' to exit." << endl;

    while (true) {
        // Prompt the user to enter a message or quit
        string receiverName, message;
        cout << "Enter receiver name and message (e.g., 'jahangir-whats up?') or 'quit': ";
        getline(cin >> ws, message);

        if (message == "quit")
            break;

        // Extract the receiver name and message from the input
        size_t separatorPos = message.find('-');
        if (separatorPos == string::npos) {
            cerr << "Invalid input format. Please use the format 'receiverName-message'." << endl;
            continue;
        }

        receiverName = message.substr(0, separatorPos);
        string actualMessage = message.substr(separatorPos + 1);

        // Prepare the message
        Message msg;
        msg.mtype = RECEIVER_TYPE;
        snprintf(msg.mtext, MAX_MESSAGE_SIZE, "%s: %s", senderName.c_str(), actualMessage.c_str());

        // Send the message to the receiver's message queue
        key_t receiverKey = ftok("chat_app", receiverName[0]);
        int receiverQueueId = msgget(receiverKey, 0666);
        if (receiverQueueId == -1) {
            cerr << "Failed to find the receiver's message queue." << endl;
            continue;
        }

        if (msgsnd(receiverQueueId, &msg, sizeof(msg.mtext), IPC_NOWAIT) == -1) {
            cerr << "Failed to send the message." << endl;
            continue;
        }

        cout << "Message sent successfully!" << endl;
    }

    // Cleanup
    msgctl(sendingQueueId, IPC_RMID, nullptr);
    msgctl(receivingQueueId, IPC_RMID, nullptr);

    return 0;
}
