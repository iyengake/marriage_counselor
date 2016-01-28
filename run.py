#!/usr/bin/python

print("Start up")
import subprocess
import time
from subprocess import Popen, PIPE
import sys
import os
# The PATH environment needed to be set in order to run Particle as a nodejs app. So I just copied it over

os.environ["PATH"]="/opt/local/bin:/opt/local/sbin:/Users/iyengark/anaconda/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/X11/bin:/Users/iyengark/scripts/"

# Create a system call to call particle subscribe on my devices
process = subprocess.Popen(["/usr/local/bin/particle", "subscribe", "mine"], stdout=subprocess.PIPE)
# Listen to the even "play_music" from my devices to indicate that music needs to be played
for line in iter(process.stdout.readline, ''):
	if "play_music" in line:
		print("Message received, playing music")
		# Set the volume to the right level
		subprocess.call(["/usr/bin/osascript", "-e", "set Volume 4"])
		# Start playing songs from my dropbox folder. VLC was the only app I could find that would play a folder of music into a list
		subprocess.call(["/usr/bin/open", "-a", "VLC", "/Users/iyengark/Dropbox/marriage_c_music/"])

