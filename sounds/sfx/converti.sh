for f in *.ogg; do ffmpeg -i "$f" "${f%.ogg}.wav"; done
for f in *.mp3; do ffmpeg -i "$f" "${f%.mp3}.wav"; done
