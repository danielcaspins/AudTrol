import socket
import os
from dotenv import load_dotenv

# Load environment variables from .env
load_dotenv()

# Read configuration from .env
HOST = os.getenv("HOST", "0.0.0.0")
PORT = int(os.getenv("PORT", 8089))
AUDIO_FOLDER = os.getenv("AUDIO_FOLDER", "audio_files")
DEFAULT_AUDIO_FILE = os.getenv("DEFAULT_AUDIO_FILE", "example.wav")

AUDIO_FILE_PATH = os.path.join(AUDIO_FOLDER, DEFAULT_AUDIO_FILE)

# Read the WAV file into memory
with open(AUDIO_FILE_PATH, "rb") as f:
    wav_data = f.read()

# Create TCP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(1)
print(f"TCP server listening on {HOST}:{PORT}")

while True:
    client_socket, addr = server_socket.accept()
    print(f"Connection from {addr}")
    try:
        # Send WAV file length first (so client knows how much to read)
        client_socket.sendall(len(wav_data).to_bytes(8, 'big'))
        # Send WAV file data
        client_socket.sendall(wav_data)
        print(f"Sent {len(wav_data)} bytes")
    except Exception as e:
        print("Error:", e)
    finally:
        client_socket.close()
