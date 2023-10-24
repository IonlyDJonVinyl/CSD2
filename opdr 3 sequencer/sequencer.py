import simpleaudio as sa
from itertools import accumulate


bpm = 120
print("The BPM is 120.")
bpmChange = input("Do you want to change the BPM? (yes/no): ")

if bpmChange.lower() == 'yes':
    new_bpm = int(input("Enter the new BPM: "))
    bpm = new_bpm
    print("The new BPM is", bpm)

amount = int(input("How many notes: "))

array=[]
for i in range(amount):
    length = float(input(f"Note {i} length?: "))
    array.append(length)

print(array)

def durations_to_timestamps(durations):
    timestamps = list(accumulate([0] + durations))
    return timestamps

timestamps = durations_to_timestamps(array)


def timestamps_to_times(timestamps, bpm):
    beat_duration = 60 / bpm
    times = [timestamp * beat_duration for timestamp in timestamps]
    return times

times = timestamps_to_times(timestamps, bpm)
print(times)