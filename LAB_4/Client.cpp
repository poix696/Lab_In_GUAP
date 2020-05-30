#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include "winsock2.h"
#include <iostream>
#include <cstdlib>
#include <clocale>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	//Инициализация winsock
	WSADATA wsaDATA;
	int res = WSAStartup(MAKEWORD(2, 2), &wsaDATA);
	if (res != NO_ERROR)
	{
		cout << "Ошибка инициализации: " << WSAGetLastError()<< endl;
		return 0;
	}
	//Создание сокета, параметры которого соответсвуют протоколу TPC
	SOCKET m_socket;
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socket == INVALID_SOCKET)
	{
		cout << "Ошибка создания сокета: " << WSAGetLastError() << endl;
		WSACleanup();
		return 0;
	}

	//соединение сокета
	struct sockaddr_in client;
	client.sin_family = AF_INET;	
	client.sin_port = htons(1234);
	client.sin_addr.S_un.S_addr = inet_addr("192.168.43.194");

	if (connect(m_socket, (SOCKADDR*)&client, sizeof(client)) == SOCKET_ERROR)
	{
		cout << "Ошибка при соединении: " <<WSAGetLastError()<< endl;
		WSACleanup();
		return 0;
	}

	//Отправка и получение данных
	char buff_send[1024];
	char buff_recv[1024];
//	gets(buff_send);
	cout << "Введите директорию и расширение файла в формате /dir1/dir2/.ext: ";
	cin >> buff_send;
	cout << endl;
	int recv_messege = SOCKET_ERROR;
	int send_messege = send(m_socket, buff_send, strlen(buff_send), 0);
	while (recv_messege == SOCKET_ERROR)
	{
		recv_messege = recv(m_socket, buff_recv, 1024, 0);
		if (recv_messege == 0 || recv_messege == WSAECONNRESET)
		{
			cout << "Соединение было сброшенно" << endl;
			break;
		}
		if (recv_messege < 0)	{return 0;}
cout<<buff_recv<<endl;
	}
	return 0;
}