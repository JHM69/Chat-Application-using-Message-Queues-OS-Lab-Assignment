# Simple Chat Application using Message Queues

A chat application implemented using message queues in C++. It allows users to send messages to each other by creating separate message queues for sending and receiving messages.

## Prerequisites

- C++ compiler (e.g., g++)
- POSIX-compliant operating system (e.g., Linux or macOS)

## Getting Started

Navigate to the project directory:

## Compile the sender.cpp and receiver.cpp files:

`g++ sender.cpp -o sender
g++ receiver.cpp -o receiver`

## Usage

Run the receiver program:

./receiver

You will be prompted to enter your name.
The receiver program will create a message queue for receiving messages.

Open a new terminal and run the sender program:

./sender

You will be prompted to enter your name.
The sender program will create a message queue for sending messages.
Start chatting!

The sender program will ask you to enter the receiver's name and your message.
The message will be sent to the receiver's message queue.
The receiver program will receive the message and display it on the screen.
Example:

Enter receiver name and message (e.g., 'jahangir-whats up?') or 'quit':
Message sent successfully!
To quit the chat application, enter 'quit' as the message in the sender program.

## How it Works

The sender program creates a message queue for sending messages using msgget() and prompts the user to enter their name.
The receiver program creates a message queue for receiving messages using msgget() and prompts the user to enter their name.
The sender program reads user input for the receiver's name and the message, extracts the receiver's name and actual message, and sends the formatted message to the receiver's message queue using msgsnd().
The receiver program continuously listens for messages in its message queue using msgrcv() and displays the received messages on the screen along with the timestamp.

Limitations
This implementation assumes that the user enters the receiver's name and message in the specified format (e.g., 'receiverName-message').
The implementation does not handle all possible edge cases or errors, and it can be further improved for robustness and error handling.
Feel free to explore and enhance the implementation based on your requirements!
