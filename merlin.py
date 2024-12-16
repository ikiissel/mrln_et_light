import os
import time
import shutil

from src.run_merlin import main_function
from src.utils.generate import run_process #vajalik labelite genereerimiseks

# MerlinSynthesizer(voice_name: str = '', merlin_path: str = '', temp_base: str = '')
#   voice_name: name of the voice to use, if not specified here, the voice must be specified in the synthesize method
#   merlin_path: path to the merlin directory, if not specified, the MERLIN_PATH environment variable will be used, if not specified, the directory of this file will be used
#   temp_base: path to the directory where temporary files will be stored, if not specified, the MERLIN_TEMP_DIR environment variable will be used, if not specified, a directory named 'temp' will be created in the merlin directory
#
# synthesize(text: str, voice: str = '') -> bytes
#   text: text to synthesize
#   voice: name of the voice to use, if not specified here, the voice must be specified in the constructor
#   returns: bytes of the wav file

class MerlinSynthesizer:
    def __init__(self, voice_name: str = '', merlin_path: str = '', temp_base: str = ''):
        self.voice = voice_name

        # Set merlin path, prioritize user input, then env variable, then default
        if merlin_path != '':
            self.merlin_path = merlin_path
        elif os.getenv('MERLIN_PATH') is not None:
            self.merlin_path = os.getenv('MERLIN_PATH', '')
        else:
            self.merlin_path = os.path.dirname(os.path.abspath(__file__))
        
        # Set temp base, prioritize user input, then env variable, then default
        if temp_base != '':
            self.temp_base = temp_base
        elif os.getenv('MERLIN_TEMP_DIR') is not None:
            self.temp_base = os.getenv('MERLIN_TEMP_DIR', '')
        else:
            self.temp_base = os.path.join(self.merlin_path, 'temp')
        if not os.path.exists(self.temp_base):
            os.mkdir(self.temp_base)


    def synthesize(self, text: str, voice: str = '') -> bytes:
        if voice == '':
            if self.voice == '':
                raise Exception('No voice specified')
            voice = self.voice

        tempDir = str(time.time()).replace('.','')
        if self.temp_base:
            tempDir = os.path.join(self.temp_base, tempDir)
        os.mkdir(tempDir)

        inPath = os.path.join(tempDir, 'in.txt')
        with open(inPath, 'w') as f:
            f.write(text)
            
        outPath = os.path.join(tempDir, 'out.wav')
        
        self._run(voice, inPath, outPath, tempDir)

        with open(outPath, 'rb') as f:
            wav = f.read()
        f.close()
        
        shutil.rmtree(tempDir)
        return wav

    def _run(self, voice, inFile, outFile, tempDir):
        os.mkdir(os.path.join(tempDir, 'prompt-lab'))

        genlab_dir = self.merlin_path + "/tools/genlab/"
        t = genlab_dir + "bin/genlab -lex " + genlab_dir + "dct/et.dct -lexd " + genlab_dir + "dct/et3.dct -o " + tempDir + "/ -f " + inFile
        run_process(t)        
     
        main_function(False, self.merlin_path, tempDir, voice)

        main_function(True, self.merlin_path, tempDir, voice)

        wavPath = os.path.join(tempDir, 'wav', '*.wav')

        run_process("sox " + wavPath + " " + outFile)
