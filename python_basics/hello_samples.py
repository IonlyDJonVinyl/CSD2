import simpleaudio as sa
import time

clap = sa.WaveObject.from_wave_file('/home/peppy/Desktop/SAMPLES/one-shots/drums/claps/TSP_NOISIA_V2_clap_clappe.wav')

amount = int(input("How many notes: "))
bpm = int(input("What is the BPM?: "))

array=[]
for i in range(amount):
    length = float(input(f"Note {i} length?: "))
    array.append(length)

print(array)

bps = bpm / 60

for length in array:
    play_obj = clap.play()
    play_obj.wait_done()
    time.sleep(length / bps)
    play_obj.wait_done()
