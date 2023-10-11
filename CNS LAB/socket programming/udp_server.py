from email import message
from socket import *
serverPort = 12000
serverSocket = socket(AF_INET,SOCK_DGRAM)
serverSocket.bind(('',serverPort))
print("Server is ready to receive")
while True:
    message,clientAddress = serverSocket.recvfrom(2048)
    reply_message = input("This is from the client")
    print(message.decode())
    serverSocket.sendto(reply_message.encode(),clientAddress)



