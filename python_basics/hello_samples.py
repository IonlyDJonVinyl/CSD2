import simpleaudio as sa


clap = sa.WaveObject.from_wave_file('/home/peppy/Desktop/SAMPLES/one-shots/drums/claps/TSP_NOISIA_V2_clap_clappe.wav')


# Get the username from the command line

username = input("Please enter your username: ")
samples = input("Please enter sample amount:")


# Print the greeting
print("Hello, " + username + "!")

for i in range(int(samples)): 
    play_obj = clap.play()
    play_obj.wait_done()

