#include <winsock2.h>
#include <ws2tcpip.h>
#include <mswsock.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

#define   Port              5000
#define   Max_Buffer_Size   4096
#define   Max_Threads       2

static GUID ax_guid = WSAID_ACCEPTEX;
static GUID as_guid = WSAID_GETACCEPTEXSOCKADDRS;

const char res_bufs[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\nWelcome to Server.";

LPFN_ACCEPTEX lpfn_AcceptEx;
LPFN_GETACCEPTEXSOCKADDRS lpfn_GetAcceptExSockAddrs;

HANDLE iocp;
SOCKET listener;

typedef struct {
    OVERLAPPED overlapped;
    SOCKET accept;
    WSABUF wsa_buf;
    CHAR buf[Max_Buffer_Size];
    DWORD bytes_send;
    DWORD bytes_recv;
    int action;
} Pre_IO_Context, *LP_Pre_IO_Context;

int init(void);
DWORD WINAPI worker_thread(LPVOID iocp);
int post_accept_ex();
int post_recv(Pre_IO_Context *io_ctx);
int post_send(Pre_IO_Context *io_ctx);
int do_accept(HANDLE iocp, Pre_IO_Context *io_ctx);
int do_recv(Pre_IO_Context *io_ctx);
int do_send(Pre_IO_Context *io_ctx);

int main(void) {
    int i;
    DWORD thread_id;
    HANDLE threads[Max_Threads];
    LINGER linger;
    SOCKADDR_IN inet_addr;

    int opt_val = 1;
    int opt_len = sizeof(int);
    printf("Win IOCP");
    if (-1 == init()) {
        printf("init failed.");
        return -1;
    }
    if ((iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0)) == NULL) {
        printf("CreateIoCompletionPort Failed，err: %d\n", GetLastError());
        return -1;
    }
    for (i = 0; i < Max_Threads; i++) {
        if ((threads[i] = CreateThread(NULL, 0, worker_thread, iocp, 0, &thread_id)) == NULL) {
            printf("CreateThread() failed. error: %d\n", GetLastError());
            CloseHandle(iocp);
            WSACleanup();
            return -1;
        }
    }
    if ((listener = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) == INVALID_SOCKET) {
        printf("WSASocket() failed. error: %d\n", WSAGetLastError());
        WSACleanup();
        return -1;
    }
    if (-1 == setsockopt(listener, SOL_SOCKET, SO_KEEPALIVE, (const void *) &opt_val, opt_len)) {
        printf("setsockopt(SO_KEEPALIVE) failed.");
        closesocket(listener);
        WSACleanup();
        CloseHandle(iocp);
        return -1;
    }
    // closesocket: return immediately and send RST
    linger.l_onoff = 1;
    linger.l_linger = 0;
    if (-1 == setsockopt(listener, SOL_SOCKET, SO_LINGER, (char *) &linger, sizeof(linger))) {
        printf("setsockopt(SO_LINGER) failed.");
        closesocket(listener);
        WSACleanup();
        CloseHandle(iocp);
        return -1;
    }
    // Windows only support SO_REUSEADDR
    if (-1 == setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (const void *) &opt_val, opt_len)) {
        printf("setsockopt(SO_REUSEADDR) failed.");
        closesocket(listener);
        WSACleanup();
        CloseHandle(iocp);
        return -1;
    }
    if (INVALID_HANDLE_VALUE == CreateIoCompletionPort((HANDLE) listener, iocp, 0, 0)) {
        printf("CreateIoCompletionPort(listener) failed.");
        closesocket(listener);
        WSACleanup();
        CloseHandle(iocp);
        return -1;
    }
    printf("Associate socket with iocp. socket: %I64d, iocp: %p \n", listener, iocp);

    inet_addr.sin_family = AF_INET;
    inet_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    inet_addr.sin_port = htons(Port);
    if (SOCKET_ERROR == bind(listener, (PSOCKADDR) &inet_addr, sizeof(inet_addr))) {
        printf("bind() failed.");
        closesocket(listener);
        WSACleanup();
        CloseHandle(iocp);
        return -1;
    }
    if (SOCKET_ERROR == listen(listener, SOMAXCONN)) {
        printf("listen() failed.");
        closesocket(listener);
        WSACleanup();
        CloseHandle(iocp);
        return -1;
    }
    printf("Listen on prot(%d).\n", Port);
    for (i = 0; i < Max_Threads; i++) {
        post_accept_ex();
    }
    // MAXIMUM_WAIT_OBJECTS
    WaitForMultipleObjects(Max_Threads, threads, FALSE, INFINITE);
    //PostQueuedCompletionStatus(iocp, 0, (DWORD)-1, NULL);
    printf("All threads exit.");
    return 0;
}


int init(void) {
    SYSTEM_INFO sys_info;
    WSADATA wsa_data;

    DWORD ret;
    SOCKET s;

    GetSystemInfo(&sys_info);

    printf("System memery page size: %d \n", sys_info.dwPageSize);
    printf("System cpus: %d \n", sys_info.dwNumberOfProcessors);
    if ((ret = WSAStartup(0x0202, &wsa_data)) != 0) {
        printf("WSAStartup() failed. error: %d\n", ret);
        return -1;
    }
    if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
        printf("Require Windows Socket Version 2.2 Error!\n");
        WSACleanup();
        return -1;
    }
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (s == -1) {
        printf("socket() failed.");
        return -1;
    }
    if (-1 == WSAIoctl(s, SIO_GET_EXTENSION_FUNCTION_POINTER, &ax_guid, sizeof(GUID),
                       &lpfn_AcceptEx, sizeof(LPFN_ACCEPTEX), &ret, NULL, NULL)) {
        printf("WSAIoctl(LPFN_ACCEPTEX) failed.");
        return -1;
    }
    if (-1 == WSAIoctl(s, SIO_GET_EXTENSION_FUNCTION_POINTER, &as_guid, sizeof(GUID),
                       &lpfn_GetAcceptExSockAddrs, sizeof(LPFN_GETACCEPTEXSOCKADDRS),
                       &ret, NULL, NULL)) {
        printf("WSAIoctl(LPFN_GETACCEPTEXSOCKADDRS) failed.");
        return -1;
    }
    if (-1 == closesocket(s)) {
        printf("closesocket() failed.");
        return -1;
    }
    return 0;
}


DWORD WINAPI worker_thread(LPVOID lp_iocp) {
    DWORD bytes;
    LP_Pre_IO_Context io_ctx;

    DWORD err_no = 0;
    HANDLE iocp = (HANDLE) lp_iocp;
    PULONG_PTR lp_completion_key = NULL;

    while (TRUE) {
        if (0 == GetQueuedCompletionStatus(iocp, &bytes, (PULONG_PTR) &lp_completion_key, (LPOVERLAPPED *) &io_ctx,
                                           INFINITE)) {
            err_no = GetLastError();
            if (err_no) {
                if (WAIT_TIMEOUT == err_no) continue;
                if (ERROR_NETNAME_DELETED == err_no || ERROR_OPERATION_ABORTED == err_no) {
                    printf("The socket was closed. error: %d\n", err_no);
                    GlobalFree(io_ctx);
                    continue;
                }
                printf("GetQueuedCompletionStatus() failed. error: %d\n", err_no);
                GlobalFree(io_ctx);
                return err_no;
            }
        }
        printf("GetQueuedCompletionStatus ---------------------------\n");
        if (NULL == io_ctx) {
            printf("GetQueuedCompletionStatus() returned no operation");
            continue;
        }
        printf("IO_Context: %p \n", io_ctx);
        printf("Bytes transferred: %d \n", bytes);
        printf("IO_Context->Action： %d\n", io_ctx->action);

        if (0 == bytes && 0 != io_ctx->action) {
            printf("No bytes transferred for the action.");
            GlobalFree(io_ctx);
            continue;
        }
        switch (io_ctx->action) {
            case 0:
                post_accept_ex();
                do_accept(iocp, io_ctx);
                post_recv(io_ctx);
                break;
            case 1:
                do_recv(io_ctx);
                post_send(io_ctx);
                break;
            case 2:
                do_send(io_ctx);
                break;
            default:
                printf("ERROR: No action match! \n");
                break;
        }
    }
}


int post_accept_ex() {
    LP_Pre_IO_Context io_ctx;
    printf("post_accept_ex. listner: %I64d\n", listener);
    if ((io_ctx = (LP_Pre_IO_Context) GlobalAlloc(GPTR, sizeof(Pre_IO_Context))) == NULL) {
        printf("GlobalAlloc() failed. error: %d\n", GetLastError());
        return -1;
    }
    ZeroMemory(&(io_ctx->overlapped), sizeof(OVERLAPPED));
    io_ctx->bytes_recv = 0;
    io_ctx->bytes_send = 0;
    io_ctx->wsa_buf.len = Max_Buffer_Size;
    io_ctx->wsa_buf.buf = io_ctx->buf;
    io_ctx->action = 0;
    io_ctx->accept = WSASocketW(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (INVALID_SOCKET == io_ctx->accept) {
        printf("WSASocketW() failed.\n");
        return -1;
    }
    if (0 == lpfn_AcceptEx(
            listener,
            io_ctx->accept,
            io_ctx->wsa_buf.buf,
            //io_ctx->wsa_buf.len - (sizeof(SOCKADDR_IN) + 16) * 2,
            0,
            sizeof(SOCKADDR_IN) + 16,
            sizeof(SOCKADDR_IN) + 16,
            &(io_ctx->bytes_recv),
            &(io_ctx->overlapped)
    )) {
        if (WSA_IO_PENDING != WSAGetLastError()) {
            printf("LPFN_ACCEPTEX() failed. last error: %d\n", WSAGetLastError());
            return -1;
        }
    }
    printf("post_accept_ex. listner: %I64d, io_ctx: %p \n", listener, io_ctx);
    return 0;
}


int do_accept(HANDLE iocp, Pre_IO_Context *io_ctx) {
    printf("do_accept. io_ctx: %p \n", io_ctx);

    SOCKADDR_IN *local_sock_addr = NULL;
    SOCKADDR_IN *remote_sock_addr = NULL;
    int addr_len = sizeof(SOCKADDR_IN);

    if (-1 == setsockopt(io_ctx->accept, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, (char *) &listener, sizeof(SOCKET))) {
        printf("setsockopt(SO_UPDATE_ACCEPT_CONTEXT) failed. error: %d\n", WSAGetLastError());
    }
    lpfn_GetAcceptExSockAddrs(
            io_ctx->wsa_buf.buf,
            io_ctx->wsa_buf.len - ((addr_len + 16) * 2),
            addr_len + 16,
            addr_len + 16,
            (SOCKADDR **) &local_sock_addr, &addr_len,
            (SOCKADDR **) &remote_sock_addr, &addr_len
    );

    printf("do_accept, client socket: %I64d \n", io_ctx->accept);

    if (NULL == CreateIoCompletionPort((HANDLE) io_ctx->accept, iocp, 0, 0)) {
        printf("CreateIoCompletionPort() failed. error: %d\n", GetLastError());
        return -1;
    }
    return 0;
}


int post_recv(Pre_IO_Context *io_ctx) {
    printf("post_recv. io_ctx: %p \n", io_ctx);

    DWORD flags = 0;
    DWORD bytes = 0;
    DWORD err_no;
    int ret;

    ZeroMemory(&(io_ctx->overlapped), sizeof(OVERLAPPED));
    io_ctx->bytes_recv = 0;
    io_ctx->bytes_send = 0;
    io_ctx->wsa_buf.len = Max_Buffer_Size;
    io_ctx->wsa_buf.buf = io_ctx->buf;
    io_ctx->action = 1;

    ret = WSARecv(io_ctx->accept, &(io_ctx->wsa_buf), 1, &bytes, &flags, &(io_ctx->overlapped), NULL);

    err_no = WSAGetLastError();
    if (-1 == ret && WSA_IO_PENDING != err_no) {
        if (err_no == WSAEWOULDBLOCK) printf("WSARecv() not ready");

        printf("WSARecv() faild. client socket: %I64d, error: %d\n", io_ctx->accept, err_no);

        return -1;
    }
    return 0;
}

int do_recv(Pre_IO_Context *io_ctx) {
    printf("do_recv. io_ctx: %p \n", io_ctx);
    printf("do_recv: recv data：\n %s \n", io_ctx->wsa_buf.buf);

    ZeroMemory(&(io_ctx->overlapped), sizeof(OVERLAPPED));
    io_ctx->bytes_recv = 0;
    io_ctx->bytes_send = 0;
    io_ctx->wsa_buf.len = Max_Buffer_Size;
    io_ctx->wsa_buf.buf = io_ctx->buf;
    io_ctx->action = 10;

    return 0;
}

int post_send(Pre_IO_Context *io_ctx) {
    printf("post_send. io_ctx: %p \n", io_ctx);

    DWORD flags = 0;
    DWORD bytes = 0;
    DWORD err_no;
    int ret;

    io_ctx->wsa_buf.buf = &res_bufs;
    io_ctx->wsa_buf.len = sizeof(res_bufs) - 1;

    //io_ctx->overlapped.hEvent = WSACreateEvent();
    io_ctx->action = 2;

    ret = WSASend(io_ctx->accept, &(io_ctx->wsa_buf), 1, &bytes, 0, &(io_ctx->overlapped), NULL);
    err_no = WSAGetLastError();

    if (-1 == ret && err_no != WSA_IO_PENDING) {
        printf("WSASend() faild. error: %d\n", err_no);

        //WSAResetEvent(io_ctx->overlapped.hEvent);
        return -1;
    }

    if (err_no == WSA_IO_PENDING) {
        printf("WSASend() posted. bytest: %d err: %d\n", bytes, err_no);
    }

    printf("WSASend send bytest: %d \n", bytes);

    /*
	WSAWaitForMultipleEvents(1, &io_ctx->overlapped.hEvent, TRUE, INFINITE, TRUE);
	printf("WSAWaitForMultipleEvents() failed. err: %d\n", WSAGetLastError());
	WSAGetOverlappedResult(io_ctx->accept, &io_ctx->overlapped, &io_ctx->bytes_send, FALSE, &flags);
	printf("WSAGetOverlappedResult() send bytes: %d\n", io_ctx->bytes_send);
	WSAResetEvent(io_ctx->overlapped.hEvent);
	printf("WSAResetEvent() err: %d\n", WSAGetLastError());
	*/
    return 0;
}


int do_send(Pre_IO_Context *io_ctx) {
    printf("do_send. io_ctx: %p \n", io_ctx);
    shutdown(io_ctx->accept, SD_BOTH);
    GlobalFree(io_ctx);
    return 0;
}