import os
import sys
import time
import shutil

sys.path.append(os.path.dirname(os.path.realpath(__file__)))
from src.run_merlin import main_function
from src.utils.generate import run_process #vajalik labelite genereerimiseks



MERLIN_PATH = os.getenv('MERLIN_PATH', os.path.dirname(os.path.abspath(__file__)))
TEMP_BASE = os.getenv('MERLIN_TEMP_DIR', os.path.join(MERLIN_PATH, 'temp'))
VOICE = os.getenv('MERLIN_VOICE')
if VOICE == None:
    print('Voice not set')
    exit(1)


def synthesize(text: str) -> bytes:
    print("TEXT:" + text)
    
    tempDir = str(time.time()).replace('.','')
    tempDir = os.path.join(TEMP_BASE, tempDir)
    os.mkdir(tempDir)

    inPath = os.path.join(tempDir, 'in.txt')
    with open(inPath, 'w') as f:
        f.write(text)
        
    outPath = os.path.join(tempDir, 'out.wav')
    
    run(inPath, outPath, tempDir)

    with open(outPath, 'rb') as f:
        wav = f.read()
    
    shutil.rmtree(tempDir)
    print("DONE:" + text)
    return wav

def run(inFile, outFile, tempDir):
    os.mkdir(os.path.join(tempDir, 'prompt-lab'))

    genlab_dir = MERLIN_PATH + "/tools/genlab/"
    t = genlab_dir + "bin/genlab -lex " + genlab_dir + "dct/et.dct -lexd " + genlab_dir + "dct/et3.dct -o " + tempDir + "/ -f " + inFile
    run_process(t)        
    #    sys.exit(1)




    #config_file = os.path.abspath(config_file)
    #cfg.configure(config_file)

    # durationModel.predict()
    # acousticModel.predict()


    main_function(False, MERLIN_PATH, tempDir, VOICE)

    main_function(True, MERLIN_PATH, tempDir, VOICE)

    wavPath = os.path.join(tempDir, 'wav', '*.wav')

    run_process("sox " + wavPath + " " + outFile)

def __main__():
    synthesize('Kas said enamvähem vastuse?')

if __name__ == '__main__':
    
    __main__()