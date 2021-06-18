wav Audio filter in C

##wav-audio-filter

This is simple wav audio filter. I coded it as a College project.

#modes:

#info
The program has a function to get information about the wav audio.

  $ wavinfo -i input

#filter

The Filter has 7 different filter modes:

1. volumn adjust:
  It allows volumn adjustment of your wavfile based on a V (0.0 ≤ V ≤ 10.0, default: 1.0).
  It basically multiplies the samples by each sample value.
  
  $ wavvol -l V -i input -o output
  
2. normalization:
    This filter makes the audio normalization, that is, the automatic volume adjustment.

  $ wavnorm -i input -o output
  
3. reverse:
  is outputs and reversed audio

  $ wavrev -i input -o output

4. echo:
  This filter outputs an echoed audio
  
  $ wavecho -t delay -l level -i input -o output
  
5. extended stereo:
  The Extended Stereo Filter allows you to increase channel separation in a stereo signal.

  $ wavwide -l k -i input -o output

6. concatenation:
  The concatenation filter receives as input one or more audio files and generates an output containing the concatenation of inputs in the indicated sequence.

  $ wavcat file1.wav file2.wav file3.wav ... -o output
  
7. mix:
  it mixes one or more wav files
  
  $ wavmix file1.wav file2.wav file3.wav ... -o output


#executing the audio-filter
  There is a makefile with the arguments to each function avaiable in the filter.
  Here's a example:
  
  $ make wavemix
  
  Then, an executable file "wavemix" will be created in the current folder.
  So, just execute the file with its respectives arguments:
  
  $ ./wavemix file1.wav file2.wav ... -o output
  
  There's a makefile option to generate all the executable files:
  
  $ make all
  
  
