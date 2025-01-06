import socket
import threading
import sys

def handle_client(client_socket, client_address):
    """
    Handles communication with a connected client.
    """
    try:
        while True:
            message = client_socket.recv(1024).decode('utf-8')
            if not message:
                break
            print(f"{message}")
    except Exception as e:
        print(f"Error with client {client_address}: {e}")
    finally:
        client_socket.close()

def start_server(port):
    """
    Starts the server and listens on the specified port.
    """
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(('0.0.0.0', port))
    server.listen(5)  # Maximum of 5 queued connections
    print(f"Server is listening on port {port}")

    try:
        while True:
            client_socket, client_address = server.accept()
            client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
            client_thread.daemon = True  # Ensures thread exits when main program exits
            client_thread.start()
    except KeyboardInterrupt:
        print("\nServer shutting down...")
    finally:
        server.close()

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python server.py <port>")
        sys.exit(1)

    try:
        port = int(sys.argv[1])
        if port < 1 or port > 65535:
            raise ValueError("Port number must be between 1 and 65535.")
        start_server(port)
    except ValueError as e:
        print(f"Invalid port: {e}")
        sys.exit(1)

