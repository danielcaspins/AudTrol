from flask import Flask, send_file

app = Flask(__name__)

@app.route("/")
def home():
    return "Audio server running on localhost:8089"

@app.route("/audio/<filename>")
def get_audio(filename):
    try:
        # Make sure the audio files are in a folder called 'audio_files'
        file_path = f"audio_files/{filename}"
        return send_file(file_path, mimetype="audio/mpeg")  # or audio/wav
    except Exception as e:
        return {"error": str(e)}, 404

if __name__ == "__main__":
    app.run(host="localhost", port=8089)
