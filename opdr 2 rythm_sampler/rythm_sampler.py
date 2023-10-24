import simpleaudio as sa


clap = sa.WaveObject.from_wave_file('/home/peppy/Desktop/SAMPLES/one-shots/drums/claps/TSP_NOISIA_V2_clap_clappe.wav')

amount = input("How many notes: ")
bpm = input("What is the BPM?: ")

array=[]
for i in range(int(amount)):
    length = float(input(f"Note {i} length?: "))
    array.append(length)

print(array)


