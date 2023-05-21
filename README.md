# Wav Audio filter in C

## Description

This is simple wav audio filter. I coded it as a College project.

## modes:

### info
The program has a function to get information about the wav audio.

```bash
$ wavinfo -i input
```

## filter

The Filter has 7 different filter modes:

### 1. volumn adjust:

It allows volumn adjustment of your wavfile based on a V (0.0 ≤ V ≤ 10.0, default: 1.0).
It basically multiplies the samples by each sample value.

```bash
$ wavvol -l V -i input -o output
```

### 2. normalization:

This filter makes the audio normalization, that is, the automatic volume adjustment.

```bash
$ wavnorm -i input -o output
```

### 3. reverse:

Is outputs and reversed audio

```bash
$ wavrev -i input -o output
```

### 4. echo:

This filter outputs an echoed audio
  
```bash
$ wavecho -t delay -l level -i input -o output
```

### 5. extended stereo:

The Extended Stereo Filter allows you to increase channel separation in a stereo signal.

```bash
$ wavwide -l k -i input -o output
```

### 6. concatenation:

The concatenation filter receives as input one or more audio files and generates an output containing the concatenation of inputs in the indicated sequence.

```bash
wavcat file1.wav file2.wav file3.wav ... -o output
```
  
7. mix:

it mixes one or more wav files

```bash
wavmix file1.wav file2.wav file3.wav ... -o output
```

## executing the audio-filter

There is a makefile with the arguments to each function avaiable in the filter.
Here's a example:

```bash
make wavemix
```

Then, an executable file "wavemix" will be created in the current folder.
So, just execute the file with its respectives arguments:

```bash
./wavemix file1.wav file2.wav ... -o output
```
  
There's a makefile option to generate all the executable files:

```bash
make all
```
