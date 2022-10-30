# How to compile:

Go to the diretory with make file -> ./Lab1/sndfile-example-src/
### 1:
    > make

### 2:
    Change the CMakeLists.txt
    > make
    > ../sndfile-example-bin/wav_hist input_wav channel
    Exemplo: ../sndfile-example-bin/wav_hist sample.wav mid
  
### 3:
    Change the CMakeLists.txt
    > make
    > ../sndfile-example-bin/wav_quant sample.wav 2 sampleQuant.wav
    reduce 14 bits by original input
  
### 4:
    Change the CMakeLists.txt
    > make
    > ../sndfile-example-bin/wav_cmp sample.wav sampleQuant.wav
    Check the SNR and maximum per sample absolute error
    
### 5:
    Change the CMakeLists.txt
    > make
    > ../sndfile-example-bin/wav_effects sample.wav sampleSingle.wav SingleEcho
    > Ganho: 0.7                  |OR         > Frequencia: 1
    > Atraso: 44100               |
    
### 6:
    It's a class, not executable
   
### 7:
    Change the CMakeLists.txt
    > make
    > ../sndfile-example-bin/encoder exemplo.texto encExemplo.txt
    
<br>
    
    Change the CMakeLists.txt
    > make
    > ../sndfile-example-bin/decoder encExemplo.txt decExemplo.txt

### 8:
    Change the CMakeLists.txt
    > make
    > ../sndfile-example-bin/lossE ...
    
<br>
    
    Change the CMakeLists.txt
    > make
    > ../sndfile-example-bin/lossD ...

## Contribuições

    Rafael Amorim -> 49%
    Diogo Fontes -> 49%
    Renato Ourives -> 2%
