from socket import *
serverName = 'hostname'
serverPort = 12000
clientSocket = socket(AF_INET,SOCK_DGRAM)
message = input('hello server')
clientSocket.sendto(message.encode,(serverName,serverPort))
reply_message,serverAddress = clientSocket.recvfrom(2048)
print(reply_message.decode())
clientSocket.close()

# import socket


# udp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
# udp.sendto()




