# sf2-smpl-packtools
gets soundfont smpl data in and out

# Usage :

put wave smpl to a new soundfont
./sf2misctool s input_soundfont new_wave_smpl output_soundfont
Example :
./sf2misctool d file.sf2pack file.wav file.sf2

extract smpl from soundfont
./sf2misctool s input_soundfont output_soundfont
Example :
./sf2misctool s file.sf2 file.wav

put any smpl to a new soundfont
./sf2misctool s input_soundfont new_smpl output_soundfont
Example :
./sf2misctool e file.sf2 file.ogg file.sf2pack
